/******************************************************************************
* ЗАДАНИЕ: bugged2.c
* ОПИСАНИЕ:
*   Еще одна программа на OpenMP с багом. 
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int nthreads, i, tid;
    float total;

    // variables were not specified as private or shared
    // according to the code below we want to compute sum of numbers of iterations given to each thread
    // so all variables are to be private except for nthreads (it's written by the 0 thread)
    // for i all works perfect without specifying

    #pragma omp parallel shared(nthreads) private(tid, total) default(none)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d is starting...\n", tid);

        // #pragma omp barrier // it's not needed here

        total = 0;
        #pragma omp for schedule(dynamic, 10)
        for (i = 0; i < 1000000; i++) {
            total = total + (float)i * 1;
//            printf ("tid = %d, i = %d, Total= %e\n", tid,i , total);
//            fflush(stdout);
        }
        printf ("Thread %d is done! Total= %e\n", tid, total);
    }
}
