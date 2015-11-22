#include <stdio.h>
#include <omp.h>
int main ()
{
    printf("This statement will always print.\n");

    /* Will only print out the statement if being compiled with -fopenmp. */
    #ifdef _OPENMP
    printf("This statement will only print when compiled with \"-fopenmp\"\n");
    #endif
    return 0;
}