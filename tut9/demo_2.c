#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    int thread_num, nthreads = 16;
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    printf("Testing OpenMP, you should see each thread print...\n");
    #pragma omp parallel
    {
        #pragma omp critical
        {
          #ifdef _OPENMP
          thread_num = omp_get_thread_num();
          printf("This thread = %d\n", thread_num);
          #endif
        }
    }
    return 0;
}