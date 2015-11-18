#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <math.h>

#define MILLION 1000000

int main(int argc, char *argv[])
{
	remove("calculations.txt");
	#ifdef _OPENMP
	if(argc == 2){
		int nthreads = atoi(argv[1]);

    	omp_set_num_threads(nthreads);
    	int n = MILLION*100;

    	float dx = 1.0/((float)n+1.0);

    	double x = 0;
    	double y = 0;
    	#pragma omp parallel for private(x)
    	for(int i = 0; i < n; i++)
    	{
	    	x = i * dx;
	    	y = exp(x)*cos(x)*sin(x)*sqrt(5*x+6.0);
	    	if((i % MILLION) == 0){
	    		#pragma omp critical
        		{
        			#ifdef _OPENMP
        			FILE* file =  fopen("calculations.txt", "a+");
        			fprintf(file, "%d: %g - %g\n", i, x, y);
        			fclose(file);
        			#endif
        		}
	    	}
	    }
	}
	#endif
	return 0;
}
