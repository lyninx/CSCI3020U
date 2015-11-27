#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define MATRIX_SIZE 100

// convenience print.
// set it up to not flood console too badly.
void print_matrix(int m[], int nleft, int nright, int ntop, int nbot)
{
	// go through each row
	for(int i = 0; i < MATRIX_SIZE; i++)
	{
		// check if this row is in vertical range
		if(i < ntop || (MATRIX_SIZE - (i + 1)) < nbot)
		{
			// print row
			for(int j = 0; j < MATRIX_SIZE; j++)
			{
				// check if this row is in horizontal range
				if(j < nleft || (MATRIX_SIZE- (j+1)) < nright)
					// print cell
					printf("\t%d", m[i*MATRIX_SIZE + j]);
				else if(j == nleft)
					// show that there are intermediate values
					printf("\t...");
			}

			// end line
			printf("\n");
		} else if (i == ntop) {
			// show that there are unshown values
			printf("\t ......\n");
		}
	}

	// end list
	printf("\n");
}

int main(int argc, char* argv[]){
	
	
	// Initialize MPI environment
	MPI_Init(&argc, &argv);


	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the rank of this process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// calculate what rows are given to which processes
	int rows_per_proc[world_size];
	int rows_per_proc_avg = MATRIX_SIZE/(world_size-1);
	rows_per_proc[0] = 0;
	for(int i = 1; i < world_size; i++)
	{
		if(i == world_size-1)
			rows_per_proc[i] = MATRIX_SIZE - rows_per_proc_avg*(world_size-2);
		else
			rows_per_proc[i] = rows_per_proc_avg;
	}


	// master process
	if(world_rank == 0)
	{
		// operand A
		int A[MATRIX_SIZE*MATRIX_SIZE];

		// operand B
		int B[MATRIX_SIZE*MATRIX_SIZE];

		// result matrix
		int C[MATRIX_SIZE*MATRIX_SIZE];


		// initialize matrices
		for(int i = 0; i < MATRIX_SIZE; i++)
		{
			for(int j = 0; j < MATRIX_SIZE; j++)
			{
				A[i*MATRIX_SIZE + j] = i;
				B[i*MATRIX_SIZE + j] = i == j ? 3 : 0;
				C[i*MATRIX_SIZE + j] = 0;
			}
		}


		// print matricies
		printf("[ MATRIX A ]:\n");
		print_matrix(A, 4, 4, 4, 4);
		printf("[ MATRIX B ]:\n");
		print_matrix(B, 4, 4, 4, 4);
		printf("[ MATRIX C ]:\n");
		print_matrix(C, 4, 4, 4, 4);

		// send each row of A
		int n_sent = 0;
		for(int i = 1; i < world_size; i++)
		{
			// figure out number of rows
			int chunk_size = MATRIX_SIZE*rows_per_proc[i];

			printf("[master] sending to %d\n", i);

			// send that chunk
			if(MPI_Send(&A[n_sent], chunk_size, MPI_INTEGER, i, n_sent, MPI_COMM_WORLD) != MPI_SUCCESS)
			{
				fprintf(stderr, "[master]Error: send A failed\n");
			}

			// update n_sent
			n_sent += chunk_size;
		}

		// broadcast B
		if(MPI_Bcast(B, MATRIX_SIZE*MATRIX_SIZE, MPI_INTEGER, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
		{
			fprintf(stderr, "[master]Error: broadcast failed\n");
		}

		// get results for C
		int n_recv = 0;
		for(int i = 1; i < world_size; i++)
		{
			// get chunk size
			int chunk_size = MATRIX_SIZE*rows_per_proc[i];

			printf("[master] recieving [%d, %d] from %d\n", n_recv, n_recv + chunk_size, i);

			// read into C
			if(MPI_Recv(&C[n_recv], chunk_size, MPI_INTEGER, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS)
			{
				fprintf(stderr, "[master]Error: recieve C from %d failed\n", i);
			}

			// update n_recv
			n_recv += chunk_size;
		}
		
		// print results
		printf("[ MATRIX C ]:\n");
		print_matrix(C, 4, 4, 4, 4);



	}
	// slave process
	else
	{
		int row_count = rows_per_proc[world_rank];
		int chunk_size = MATRIX_SIZE*row_count;
		MPI_Status status;
		int A_chunk[chunk_size];
		int B[MATRIX_SIZE*MATRIX_SIZE];
		int C_chunk[chunk_size];
		MPI_Recv(A_chunk, chunk_size, MPI_INTEGER, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		int n_sent = status.MPI_TAG;

		printf("[proc %d] recieved chunk [%d, %d)\n", world_rank, n_sent, n_sent + chunk_size);


		MPI_Bcast(B, MATRIX_SIZE*MATRIX_SIZE, MPI_INTEGER, 0, MPI_COMM_WORLD);
		printf("[proc %d] recieved B\n", world_rank);

		// do calculations
		for(int i = 0; i < row_count; i++)
			for(int j = 0; j < MATRIX_SIZE; j++)
				for(int k = 0; k < MATRIX_SIZE; k++)
					C_chunk[i*MATRIX_SIZE + j] = A_chunk[i*MATRIX_SIZE + k] * B[k*MATRIX_SIZE + j];

		// return result
		printf("[proc %d] sending result\n", world_rank);
		MPI_Send(C_chunk, chunk_size, MPI_INTEGER, 0, 0, MPI_COMM_WORLD);



	}


	// done with this environment
	MPI_Finalize();



}