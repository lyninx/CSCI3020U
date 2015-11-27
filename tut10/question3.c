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
				B[i*MATRIX_SIZE + j] = j;
				C[i*MATRIX_SIZE + j] = 0;
			}
		}

		// broadcast each row of A
		for(int i = 0; i < MATRIX_SIZE; i++)
		{
			//MPI_Send((void*)A[i], MATRIX_SIZE, MPI_INTEGER, i % world_size)
		}

		//todo

		// print results
		printf("[ MATRIX A ]:\n");
		print_matrix(A, 4, 4, 4, 4);
		printf("[ MATRIX B ]:\n");
		print_matrix(B, 4, 4, 4, 4);
		printf("[ MATRIX C ]:\n");
		print_matrix(C, 4, 4, 4, 4);


	}
	// slave process
	else
	{

	}


	// done with this environment
	MPI_Finalize();



}