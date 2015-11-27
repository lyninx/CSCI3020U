#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define MATRIX_SIZE 100

#define MASTER_PROC 0

/**
* convenience print.
* set it up to not flood console too badly.
**/
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

/**
* Master procedure;
* Calculates product of matricies 'A' and 'B' AB and stores in 'C'.
* The work is split up into procedures depending on the number of rows
* specified in 'rows_per_proc', which has a size equal to the number of
* procedures indicated by 'world_size'.
**/
void multiply_matricies_master(int A[], int B[], int C[], int world_size, int rows_per_proc[])
{
	// send each row of A
	int n_sent = 0;
	for(int i = 0; i < world_size; i++)
	{
		if(i != MASTER_PROC)
		{
			// figure out number of rows
			int chunk_size = MATRIX_SIZE*rows_per_proc[i];

			// send that chunk
			if(MPI_Send(&A[n_sent], chunk_size, MPI_INTEGER, i, n_sent, MPI_COMM_WORLD) != MPI_SUCCESS)
			{
				fprintf(stderr, "[master]Error: send A failed\n");
			}

			// update n_sent
			n_sent += chunk_size;
		}
	}

	// broadcast B
	if(MPI_Bcast(B, MATRIX_SIZE*MATRIX_SIZE, MPI_INTEGER, MASTER_PROC, MPI_COMM_WORLD) != MPI_SUCCESS)
	{
		fprintf(stderr, "[master]Error: broadcast failed\n");
	}

	// get results for C
	int n_recv = 0;
	for(int i = 0; i < world_size; i++)
	{
		if(i != MASTER_PROC)
		{
			// get chunk size
			int chunk_size = MATRIX_SIZE*rows_per_proc[i];

			// read into C
			if(MPI_Recv(&C[n_recv], chunk_size, MPI_INTEGER, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS)
			{
				fprintf(stderr, "[master]Error: recieve C from %d failed\n", i);
			}

			// update n_recv
			n_recv += chunk_size;

		}
	}
}

/**
* Slave procedure;
* Calculates product AB for 'row_count' rows.
**/
void multiply_matricies_slave(int row_count)
{
	// size of array to recieve
	int chunk_size = MATRIX_SIZE*row_count;

	// slice of A for this proc
	int A_chunk[chunk_size];

	// operand B
	int B[MATRIX_SIZE*MATRIX_SIZE];

	// slice of C for this proc
	int C_chunk[chunk_size];


	// initialize C to 0
	for(int i = 0; i < chunk_size; i++)
		C_chunk[i] = 0;

	// status of recieved data
	MPI_Status status;

	// recieve slice of A
	MPI_Recv(A_chunk, chunk_size, MPI_INTEGER, MASTER_PROC, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	// recieve B
	MPI_Bcast(B, MATRIX_SIZE*MATRIX_SIZE, MPI_INTEGER, MASTER_PROC, MPI_COMM_WORLD);

	// put result of matrix multiplication into C slice
	for(int i = 0; i < row_count; i++)
		for(int j = 0; j < MATRIX_SIZE; j++)
			for(int k = 0; k < MATRIX_SIZE; k++)
				C_chunk[i*MATRIX_SIZE + j] += A_chunk[i*MATRIX_SIZE + k] * B[k*MATRIX_SIZE + j];

	// send C slice back to master proc
	MPI_Send(C_chunk, chunk_size, MPI_INTEGER, MASTER_PROC, 0, MPI_COMM_WORLD);
}

/**
* Driver
**/
int main(int argc, char* argv[]){
	
	
	// Initialize MPI environment
	MPI_Init(&argc, &argv);


	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the rank of this process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// number of rows allocated to each process
	int rows_per_proc[world_size];

	// number of rows allocated to each process, but like floored or something.
	int rows_per_proc_avg = MATRIX_SIZE/(world_size-1);

	// calculate what rows are given to which processes
	for(int i = 0; i < world_size; i++)
	{
		if(i == MASTER_PROC)
			// master process ain't doing any of this.
			rows_per_proc[i] = 0;
		else if(i == world_size-1 || (i == world_size-2 && MASTER_PROC == world_size-1))
			// the last slave process will take on the remaining rows.
			rows_per_proc[i] = MATRIX_SIZE - rows_per_proc_avg*(world_size-2);
		else
			// assign the number we calculated before to most slaves.
			rows_per_proc[i] = rows_per_proc_avg;
	}


	// split depending on proc number
	if(world_rank == MASTER_PROC)
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
				// initialize A to the row number
				A[i*MATRIX_SIZE + j] = i+1;

				// have B be diagonal with increasing entries
				B[i*MATRIX_SIZE + j] = i == j ? i+1 : 0;
			}
		}

		// print matricies
		printf("[ MATRIX A %dx%d ]:\n", MATRIX_SIZE, MATRIX_SIZE);
		print_matrix(A, 4, 4, 4, 4);
		printf("[ MATRIX B %dx%d ]:\n", MATRIX_SIZE, MATRIX_SIZE);
		print_matrix(B, 4, 4, 4, 4);

		// multiply em
		multiply_matricies_master(A, B, C, world_size, rows_per_proc);
		
		// print results
		printf("[ MATRIX C %dx%d ]:\n", MATRIX_SIZE, MATRIX_SIZE);
		print_matrix(C, 4, 4, 4, 4);
	}
	else
	{
		// slave process
		multiply_matricies_slave(rows_per_proc[world_rank]);
	}

	// done with this procedure
	MPI_Finalize();



}