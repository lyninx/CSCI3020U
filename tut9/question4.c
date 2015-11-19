#include <stdio.h>

#define M_SIDE 100

// runtime
int main(void);

// convenience; prints the contents of an array
// nleft etc parameters specify how many should be read on each side, rest
// are truncated
void print_matrix(int m[M_SIDE][M_SIDE], int nleft, int nright, int ntop, int nbot);



int main(void)
{
	// create matrices
	int a[M_SIDE][M_SIDE], b[M_SIDE][M_SIDE];

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

	// verify solution somehow

	//done
	return 0;
}

void print_matrix(int m[M_SIDE][M_SIDE], int nleft, int nright, int ntop, int nbot)
{
	for(int i = 0; i < M_SIDE; i++)
	{
		if(i < ntop || (M_SIDE - (i + 1)) < nbot)
		{

			for(int j = 0; j < M_SIDE; j++)
			{
				if(j < nleft || (M_SIDE - (j+1)) < nright)
					printf("%d\t", m[i][j]);
				else if(j == nleft)
					printf("...\t");
			}
			printf("\n");
		} else if (i == ntop) {
			printf("...\n");
		}
	}
	printf("\n");
}