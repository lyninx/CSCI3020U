#include <stdio.h>
#include <stdbool.h>

#define M_SIDE 100

// runtime
int main(void);

// convenience; prints the contents of an array
// nleft etc parameters specify how many should be read on each side, rest
// are truncated
void print_matrix(int m[M_SIDE][M_SIDE], int nleft, int nright, int ntop, int nbot);

// verification of matrice solution.
bool verify_matrix(int a[M_SIDE][M_SIDE], int b[M_SIDE][M_SIDE], int sol[M_SIDE][M_SIDE])
{
	//todo
	return false;
}

// performs matrix multiplication
void multiply_matrix(int a[M_SIDE][M_SIDE], int b[M_SIDE][M_SIDE], int dest[M_SIDE][M_SIDE])
{
	//todo
	dest[0][0] = 1;
	dest[0][1] = 2;
}

int main(void)
{
	// create matrices
	int a[M_SIDE][M_SIDE], b[M_SIDE][M_SIDE], ab[M_SIDE][M_SIDE];

	//initialize matrices
	for(int i = 0; i < M_SIDE; i++)
	{
		for(int j = 0; j < M_SIDE; j++)
		{
			a[i][j] = i+j+2;
			b[i][j] = i+j;
		}
	}

	// print em
	printf("Matrix A:\n");
	print_matrix(a, 4, 4, 4, 4);
	printf("Matrix B:\n");
	print_matrix(b, 4, 4, 4, 4);

	// multiply them
	multiply_matrix(a, b, ab);

	//print it
	printf("Matrix AB:\n");
	print_matrix(ab, 4, 4, 4, 4);


	// verify solution somehow
	if(!verify_matrix(a, b, ab))
	{
		fprintf(stderr, "Error: ab is bad\n");
		return 1;
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
					printf("...\t");
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