#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#define T_NUM 3

long double long_sum_it(long int k);
long double pow_2(long int k);
long double m_sum(const long double * x, int size);
long double Leibniz_it(long int k);
long double Leibniz(long int N);
long double long_sum(long int N);
int comp(long double x, long double y);

int main(int argc, char **argv) {

    omp_set_num_threads(T_NUM);
    long int N = 0;
    long double sum[T_NUM];
    char * end_ptr;
    N = strtol(argv[1], &end_ptr, 10);
    omp_set_num_threads(T_NUM);
    // pi = 3,1415926535 8979323846 2643383279
    long double res = long_sum(N);
    printf("N = %ld\n", N);
    printf("actual pi:       3.1415926535897932\n");
    printf("long_sum result: %.16lf\n", (double) res);
    res = Leibniz(N);
    printf("Leibniz result:  %.16lf\n", (double) res);

    return 0;
}

long double long_sum_it(long int k){
    long double kk = (long double) k;
    long double res;
    if(k % 2){
        res = -(1/(4*kk+3) + 2/(4*kk+2) + 2/(4*kk+1)) / pow_2(2*k);
    } else {
        res = (1/(4*kk+3) + 2/(4*kk+2) + 2/(4*kk+1)) / pow_2(2*k);
    }
    return res;
}

long double Leibniz_it(long int k){
    long double kk = (long double) k;
    long double res;
    if(k % 2){
        res = -(1/(2*kk+1));
    } else {
        res = (1/(2*kk+1));
    }
    return res;
}

long double pow_2(long int k){
    unsigned long long int one = 1;
    return (long double) (one << k);
}

long double m_sum(const long double * x, int size){
    long double res = 0;
    qsort((void *) x, T_NUM, sizeof(long double), (int(*) (const void *, const void *)) comp);
//    for (int i = 0; i < T_NUM; ++i) {
//        printf("%.16lf ", (double) x[i]);
//    }
//    printf("\n");
    for (int i = size-1; i >= 0; i--) {
        res += x[i];
    }
    return res;
}

int comp(const long double x, const long double y){
    if (fabsl(x) < fabsl(y)) return 1;
    if (fabsl(x) > fabsl(y)) return -1;
    return 0;
}

long double long_sum(long int N){
    long double * sum = malloc(T_NUM * sizeof(long double));
#pragma omp parallel shared(N, sum) default (none)
    {
        int id = omp_get_thread_num();
        sum[id] = 0;
#pragma omp  for schedule(guided)
        for (int i = 0; i < N; i++) {
            sum[id] = long_sum_it(N-i-1) + sum[id];
        }
    }
    long double res = m_sum(sum, T_NUM);
    free(sum);
    return res;
}

long double Leibniz(long int N){
    long double * sum = malloc(T_NUM * sizeof(long double));
#pragma omp parallel shared(N, sum) default (none)
    {
        int id = omp_get_thread_num();
        sum[id] = 0;
#pragma omp  for schedule(guided)
        for (int i = 0; i < N; i++) {
            sum[id] = Leibniz_it(N-i-1) + sum[id];
        }
    }
    long double res = m_sum(sum, T_NUM);
    free(sum);
    return res*4;
}
