#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define MATRIX_SIZE 100

// convenience print.
// set it up to not flood console too badly.
void print_matrix(int m[MATRIX_SIZE][MATRIX_SIZE], int nleft, int nright, int ntop, int nbot)
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
					printf("\t%d", m[i][j]);
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

	// get number of procs
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the rank of this process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// Get processor name
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	// Print stuff
	printf("processor %s, rank %d/%d\n", processor_name, world_rank, world_size);

	// master process
	if(world_rank == 0)
	{
		// operand A
		int A[MATRIX_SIZE][MATRIX_SIZE];

		// operand B
		int B[MATRIX_SIZE][MATRIX_SIZE];

		// result matrix
		int C[MATRIX_SIZE][MATRIX_SIZE];

		// initialize matrices
		for(int i = 0; i < MATRIX_SIZE; i++)
		{
			for(int j = 0; j < MATRIX_SIZE; j++)
			{
				A[i][j] = i;
				B[i][j] = j;
				C[i][j] = 0;
			}
		}

		//todo

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