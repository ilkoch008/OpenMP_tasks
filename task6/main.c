#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#define T_NUM 4

struct number {
    int value;
    int is_prime;
} number;

struct starter_pack {
    int * prime_nums;
    int size;
} starterPack;

struct starter_pack sieve_of_Eratosthenes(struct number * numbers, int size);
int is_not_prime(int x, struct starter_pack pack);

int main(int argc, char **argv) {
    omp_set_num_threads(T_NUM);
    double end, start, res;
    long int N = 0;
    long double sum[T_NUM];
    char * end_ptr;
    N = strtol(argv[1], &end_ptr, 10);
    int sqrt_N = (int) sqrtf((float) N) + 2;
    struct number * numbers = malloc(N * sizeof(number));
    for (int i = 0; i < N; ++i) {
        numbers[i].value = i + 2;
        numbers[i].is_prime = 1;
    }

    start = omp_get_wtime();

    struct starter_pack pack = sieve_of_Eratosthenes(numbers, sqrt_N);

#pragma omp parallel shared(N, pack, sqrt_N, numbers) default (none)
    {
#pragma omp  for schedule(guided)
        for (int i = sqrt_N; i < N; i++) {
            if(is_not_prime(numbers[i].value, pack)){
                numbers[i].is_prime = 0;
            }
        }
    }

//    for (int i = 0; i < N; ++i) {
//        if(numbers[i].is_prime){
//            printf("%d ", numbers[i].value);
//        }
//    }
//    printf("\n");

    end = omp_get_wtime();
    res = end - start;
    printf("execution time: %f\n", res);
    return 0;
}

struct starter_pack sieve_of_Eratosthenes(struct number * numbers, int size){
    struct starter_pack res;
    res.size = 0;
    for (int i = 0; i < size; ++i) {
        if(numbers[i].is_prime){
            res.size++;
            for (int j = i + numbers[i].value; j < size; j += numbers[i].value) {
                numbers[j].is_prime = 0;
            }
        }
    }

    res.prime_nums = malloc(res.size * sizeof(int));
    int j = 0;
    for (int i = 0; i < size; ++i) {
        if(numbers[i].is_prime){
            res.prime_nums[j] = numbers[i].value;
            j++;
        }
    }
    return res;
}

int is_not_prime(int x, struct starter_pack pack){
    for (int i = 0; i < pack.size; ++i) {
        if (x % pack.prime_nums[i] == 0){
            return 1;
        }
    }
    return 0;
}
