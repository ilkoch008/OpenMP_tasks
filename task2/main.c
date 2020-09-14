#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define T_NUM 3

int main(int argc, char **argv) {

    omp_set_num_threads(T_NUM);
    long int N = 0, sum = 0;
    char * end_ptr;
    N = strtol(argv[1], &end_ptr, 10);
    printf("N: %ld\n", N);
    double end, start = omp_get_wtime();
#pragma omp parallel shared(N) reduction(+: sum) default (none)
    {
#pragma omp  for schedule(static)
        for (int i = 1; i <= N; i++)
            sum += i;
    }

    end = omp_get_wtime();
    double time = end - start;
    printf("result: %ld\n", sum);
    printf("time: %f\n", time);
    return 0;
}
