#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <math.h>

#define MILLION 1000000

int main(int argc, char *argv[])
{
	remove("calculations.txt");
	if(argc == 2){
		int nthreads = atoi(argv[1]);

        #ifdef _OPENMP
    	omp_set_num_threads(nthreads);
        #endif
    	int n = MILLION*100;

    	float dx = 1.0/((float)n+1.0);

    	double x = 0;
    	double y = 0;
    	#pragma omp parallel for private(x)
    	for(int i = 0; i < n; i++)
    	{
	    	x = i * dx;
	    	y = exp(x)*cos(x)*sin(x)*sqrt(5*x+6.0);
	    	if((i % MILLION) == 0 && i != 0){
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
	return 0;
}
