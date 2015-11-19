#include <stdio.h>
#include <stdbool.h>
#include <omp.h>

/// size length of matrix
#define M_SIDE 100

/// value of B Matrix
#define M_FACTOR 3

// number of threads to use
#define N_THREADS 16

/// runtime
int main(void);

/// Convenience; Prints the contents of an array.
/// Parameters 'nleft' etc. specify how many should be read on each side, rest
/// are truncated
void print_matrix(int m[M_SIDE][M_SIDE], int nleft, int nright, int ntop, int nbot);

/// Convienience; Provides highly specific verification of matrice solution.
bool verify_matrix(int orig[M_SIDE][M_SIDE], int trans[M_SIDE][M_SIDE]);

/// Function that multiplies matrices a & b; storing product in 'dest'.
void multiply_matrix(int a[M_SIDE][M_SIDE], int b[M_SIDE][M_SIDE], int dest[M_SIDE][M_SIDE]);


// performs matrix multiplication
// @param a: operand 1
// @param b: operand 2
// @param dest: destination array for product.
// all matricies must be arrays of size 100 x 100.
void multiply_matrix(int a[M_SIDE][M_SIDE], int b[M_SIDE][M_SIDE], int dest[M_SIDE][M_SIDE])
{
	// initialize number of threads
	#ifdef _OPENMP
	omp_set_num_threads(N_THREADS);
	#endif

	// iteration values
	int i = 0;
	int j = 0;
	int k = 0;

	// initialize destination matrix to 0 with threads
	#pragma omp parallel for shared(dest) private(i, j) collapse(2)
	for(i = 0; i < M_SIDE; ++i)
		for(j = 0; j < M_SIDE; ++j)
			dest[i][j] = 0;

	// term product to use in array
	int prod = 0;

	// use threads to calculate the value of each element.
	// - shared: operands and destinaton.
	// - private: iteration values are given private instances across each thread
	// - schedule: assign each thread a certain number of iterations based on the chunk size
	// - "collapse(3)": this is a triple-nested for loop.
	#pragma omp parallel for shared(a, b, dest) private(i, j, k, prod) schedule(dynamic, M_SIDE) collapse(3)
	for(i = 0; i < M_SIDE; ++i) {
		for(j = 0; j < M_SIDE; ++j) {	
			for(k = 0; k < M_SIDE; ++k)
			{
				// calculate term a(i, k) * b(k, j)
				prod = a[i][k] * b[k][j];

				// add term to value of ab(i, j)
				#pragma omp critical
				{
					dest[i][j] += prod;
				}
			}
		}
	}

}

// convenience print.
// set it up to not flood console too badly.
void print_matrix(int m[M_SIDE][M_SIDE], int nleft, int nright, int ntop, int nbot)
{
	// go through each row
	for(int i = 0; i < M_SIDE; i++)
	{
		// check if this row is in vertical range
		if(i < ntop || (M_SIDE - (i + 1)) < nbot)
		{
			// print row
			for(int j = 0; j < M_SIDE; j++)
			{
				// check if this row is in horizontal range
				if(j < nleft || (M_SIDE - (j+1)) < nright)
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

/// Provides verification of matrice solution.
bool verify_matrix(int orig[M_SIDE][M_SIDE], int trans[M_SIDE][M_SIDE])
{
	// iteration values
	int i = 0;
	int j = 0;

	// number of errors caught by all threads
	int nerrors = 0;


	// use threads to check each element of array.
	#pragma omp parallel for shared(orig, trans) private(i, j) collapse(2) reduction(+: nerrors)
	for(i = 0; i < M_SIDE; ++i)
	{
		for(j = 0; j < M_SIDE; ++j)
		{
			// 
			if(trans[i][j] != M_FACTOR*orig[i][M_SIDE - j - 1])
				nerrors += 1;
		}
	}

	return nerrors == 0;
}


int main(void)
{

	// create matrices
	int a[M_SIDE][M_SIDE], b[M_SIDE][M_SIDE], ab[M_SIDE][M_SIDE];
	
	// initialize matrices
	// the output for the program explains what's going on here ('blah blah blah')
	for(int i = 0; i < M_SIDE; i++)
	{
		for(int j = 0; j < M_SIDE; j++)
		{
			a[i][j] = (i*M_SIDE)+j+1;
			b[i][j] = (M_SIDE - 1 - i) == j ? M_FACTOR : 0;
		}
	}

	// multiply them
	multiply_matrix(a, b, ab);

	// This is all just console output; Everything here is just like 'blah blah blah'
	{
		printf("Matrix A [%dx%d]:\n", M_SIDE, M_SIDE);
		print_matrix(a, 3, 2, 3, 2);
		printf("Matrix B [%dx%d]:\n", M_SIDE, M_SIDE);
		print_matrix(b, 3, 2, 3, 2);
		printf("Matrix AB [%dx%d]:\n", M_SIDE, M_SIDE);
		print_matrix(ab, 3, 2, 3, 2);

		// explain parameters
		printf("Explanation:\nMatrix A's cells are initialized to the iteration number.\n");
		printf("Matrix B is intialized to I*%d, inverted horizontally.\n", M_FACTOR);
		printf("The product AB should therefore be equal to A*%d, inverted horizontally.\n\nResults:\n", M_FACTOR);
	}
	

	// verify solution
	if(!verify_matrix(a, ab))
	{
		// someone messed up.
		printf("However, This was not found to be true.\n");
		fprintf(stderr, "Error: ab is bad\n");
		return 1;
	} else {
		// it's k.
		printf("The product AB was found to fit those parameters --> this product was accurate.\n\n");
		return 0;
	}
}