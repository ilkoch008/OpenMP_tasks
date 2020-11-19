/******************************************************************************
* ЗАДАНИЕ: bugged6.c
* ОПИСАНИЕ:
*   Множественные ошибки компиляции
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VECLEN 100

float a[VECLEN], b[VECLEN];

float dotprod()
{
    int i, tid;
    float sum;
#pragma omp parallel private(tid) shared(a,b,sum) default(none) // this must be here (with some modifications)
    {
        tid = omp_get_thread_num();
#pragma omp for reduction(+:sum)
        for (i = 0; i < VECLEN; i++) {
            sum = sum + (a[i] * b[i]);
            printf("  tid= %d i=%d\n", tid, i);
        }
    }
    return sum; // we weren't returning anything from nonvoid function
}


int main (int argc, char *argv[])
{
    int i;
    float sum;

    for (i = 0; i < VECLEN; i++)
        a[i] = b[i] = (float)1.0 * (float)i;

    //#pragma omp parallel shared(sum) // this must be in another place
    sum = dotprod(); // we weren't assigning new sum value to anything

    printf("Sum = %f\n",sum);
}


