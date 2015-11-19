#include <stdio.h>
#include <stdbool.h>
#include <omp.h>

#define M_SIDE 100

#define M_FACTOR 1

// runtime
int main(void);

// convenience; prints the contents of an array
// nleft etc parameters specify how many should be read on each side, rest
// are truncated
void print_matrix(int m[M_SIDE][M_SIDE], int nleft, int nright, int ntop, int nbot);

// verification of matrice solution.
bool verify_matrix(int orig[M_SIDE][M_SIDE], int trans[M_SIDE][M_SIDE])
{
	int i = 0;
	int j = 0;
	int nerrors = 0;

	#pragma omp parallel for shared(orig, trans) private(i, j) collapse(2) reduction(+: nerrors)
	for(i = 0; i < M_SIDE; ++i)
	{
		for(j = 0; j < M_SIDE; ++j)
		{
			if(trans[i][j] != M_FACTOR*orig[i][M_SIDE - j - 1])
				nerrors += 1;
		}
	}

	return nerrors == 0;
}

// performs matrix multiplication
void multiply_matrix(int a[M_SIDE][M_SIDE], int b[M_SIDE][M_SIDE], int dest[M_SIDE][M_SIDE])
{
	int nthreads = 16;
	#ifdef _OPENMP
	omp_set_num_threads(nthreads);
	#endif

	int i = 0;
	int j = 0;
	int k = 0;

	// initialize to 0
	#pragma omp parallel for shared(dest) private(i, j) collapse(2)
	for(i = 0; i < M_SIDE; ++i)
		for(j = 0; j < M_SIDE; ++j)
			dest[i][j] = 0;

	// sum values
	int prod = 0;
	#pragma omp parallel for shared(a, b, dest) private(i, j, k, prod) collapse(3) schedule(dynamic, M_SIDE)
	for(i = 0; i < M_SIDE; ++i)
	{
		for(j = 0; j < M_SIDE; ++j)
		{	
			// calculate cell a(i, j)
			for(k = 0; k < M_SIDE; ++k)
			{

				prod = a[i][k] * b[k][j];

				#pragma omp critical
				{
					dest[i][j] += prod;
				}
			}


		}
	}

}

int main(void)
{
	// print information
	printf("TUTORIAL 9 QUESTION 4:\n");

	// create matrices
	int a[M_SIDE][M_SIDE], b[M_SIDE][M_SIDE], ab[M_SIDE][M_SIDE];

	// explain what these arrays are gonna be.
	printf("\t- Matrix A's cells will be initialized to the iteration number.\n");
	printf("\t- Matrix B will be intialized to I*%d, inverted horizontally.\n", M_FACTOR);
	printf("\t the product AB should therefore be equal to A*%d, inverted horizontally.\n", M_FACTOR);

	//initialize matrices
	for(int i = 0; i < M_SIDE; i++)
	{
		for(int j = 0; j < M_SIDE; j++)
		{
			a[i][j] = i*M_SIDE+j+1;
			b[i][j] = (M_SIDE - 1 - i) == j ? M_FACTOR : 0;
		}
	}

	// print em
	printf("Matrix A [%dx%d]):\n", M_SIDE, M_SIDE);
	print_matrix(a, 4, 4, 4, 4);
	printf("Matrix B [%dx%d]:\n", M_SIDE, M_SIDE);
	print_matrix(b, 4, 4, 4, 4);

	// multiply them
	multiply_matrix(a, b, ab);

	//print it
	printf("Matrix AB [%dx%d]:\n", M_SIDE, M_SIDE);
	print_matrix(ab, 4, 4, 4, 4);


	// verify solution somehow
	if(!verify_matrix(a, ab))
	{
		fprintf(stderr, "Error: ab is bad\n");
		return 1;
	} else {
		printf("AB was found to fit these parameters --> this product was accurate.\n");
	}

	//done
	return 0;
}

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
					printf("%d\t", m[i][j]);
				else if(j == nleft)
					// show that there are intermediate values
					printf("...");
			}

			// end line
			printf("\n");
		} else if (i == ntop) {
			// show that there are unshown values
			printf("...\n");
		}
	}

	// end list
	printf("\n");
}