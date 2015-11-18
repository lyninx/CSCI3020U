#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

#define MILLION 100000000

int main (int argc, char *argv[])
{
	if (argc == 2) {
		int nthreads = atoi(argv[1]);
		int n = MILLION;
		double x, y[n];

		double dx = 1.0/(n+1.0);

		#ifdef _OPENMP
	    omp_set_num_threads(nthreads);
	    #endif

	    #pragma omp parallel for private(x)
	    for (int i=0; i<n; i++) {
	    	x = i*dx;
	    	y[i] = exp(x)*cos(x)*sin(x)*sqrt(5*x+6.0);
	    }
	}
    return 0;
}