#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    int thread_num, nthreads = 16;

    /* Will set the number of threads if compiled with -fopenmp. */
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    printf("Testing OpenMP, you should see each thread print...\n");
    
    /* Creates a team of threads and all threads will execute this block of code. */
    #pragma omp parallel
    {
        /* Specifies that this section of code must be executed by one thread at a time. */ 
        #pragma omp critical
        {
          /* Will print out the number of the thread if compiled with -fopenmp. */
          #ifdef _OPENMP
          thread_num = omp_get_thread_num();
          printf("This thread = %d\n", thread_num);
          #endif
        }
    }
    return 0;
}