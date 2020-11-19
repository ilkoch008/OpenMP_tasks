/******************************************************************************
* ЗАДАНИЕ: bugged4.c
* ОПИСАНИЕ:
*   Очень простая программа с segmentation fault.
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1048

int main (int argc, char *argv[]) 
{
    int nthreads, tid, i, j;
    double ** a; // that was toooo big
                 // and since (a) used as private we should allocate memory in parallel section


    #pragma omp parallel shared(nthreads) private(i, j, tid, a) default(none)
    {
        a = malloc(N * sizeof(double*));
        for (int k = 0; k < N; ++k) {
            a[k] = malloc(N * sizeof(double));
        }
        tid = omp_get_thread_num();
        if (tid == 0) 
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d starting...\n", tid);

        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                a[i][j] = tid + i + j;

        printf("Thread %d done. Last element= %f\n", tid, a[N-1][N-1]);
        for (int k = 0; k < N; ++k) {
            free(a[k]);
        }
        free(a);
    }


}
