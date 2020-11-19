/******************************************************************************
* ЗАДАНИЕ: bugged5.c
* ОПИСАНИЕ:
*   Используя секции, два потока инициализируют свои личные массивы
*   и затем добавляют свой массив в массивы соседа.
*   Почему-то происходит deadlock...
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N     1000000
#define PI    3.1415926535
#define DELTA .01415926535

int main (int argc, char *argv[]) 
{
    int nthreads, tid, i;
    float * a, * b;
    a = malloc(N * sizeof(float));
    b = malloc(N * sizeof(float));
    omp_lock_t locka, lockb;

    omp_init_lock(&locka);
    omp_init_lock(&lockb);

    for (i = 0; i < N; i++) {
        a[i]=0;
        b[i]=0;
    }

    #pragma omp parallel shared(a, b, nthreads, locka, lockb) private(tid, i) default(none)
    {
        tid = omp_get_thread_num();
        #pragma omp master
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d starting...\n", tid);
        #pragma omp barrier

        #pragma omp sections nowait
        { // it doesn't seem like it matches the description but who am I to argue
            #pragma omp section
            {
                omp_set_lock(&locka);
                printf("Thread %d updating a[]\n", tid);
                for (i = 0; i < N; i++)
                    a[i] += (float)DELTA * (float)i;
                omp_unset_lock(&locka); // letting go a after updating
                omp_set_lock(&lockb);   // and locking b (here was a deadlock, both locks was locked and both threads
                                        // were trying to lock other lock (lock lock lock...))
                printf("Thread %d updating b[]\n", tid);
                for (i = 0; i < N; i++)
                    b[i] += (float)DELTA + (float)i;
                omp_unset_lock(&lockb);
            }

            #pragma omp section
            {
                omp_set_lock(&lockb);
                printf("Thread %d updating b[]\n", tid);
                for (i = 0; i < N; i++)
                    b[i] += (float)PI * (float)i;
                omp_unset_lock(&lockb); // letting go b after updating
                omp_set_lock(&locka);   // and locking a
                printf("Thread %d adding b[] to a[]\n", tid);
                for (i = 0; i < N; i++)
                    a[i] += (float)PI + (float)i;
                omp_unset_lock(&locka);
            }
        }
    }
    printf("Sample results: %f %f %f %f\n", a[0], b[0], a[999999], b[999999]);
    free(a);
    free(b);
}
