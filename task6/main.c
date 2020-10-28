#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#define T_NUM 4

// it is more convenient to simply mark the numbers as needed than to remove numbers from the array
struct number {
    int value;
    int is_prime;
} number;

// the part of numbers that is processed sequentially,
// and then used by the parallel algorithm to check
struct starter_pack {
    int * prime_nums;
    int size;
} starterPack;


struct starter_pack sieve_of_Eratosthenes(struct number * numbers, int size);

// checks if number is prime using pack
int is_not_prime(int x, struct starter_pack pack);

int main(int argc, char **argv) {
    omp_set_num_threads(T_NUM);
    double end, start, res;
    long int N = 0;
    long double sum[T_NUM];
    char * end_ptr;
    N = strtol(argv[1], &end_ptr, 10);
    //N = 1000;
    int sqrt_N = (int) sqrtf((float) N) + 2;
    struct number * numbers = malloc(N * sizeof(number));
    for (int i = 0; i < N; ++i) {
        numbers[i].value = i + 2;
        numbers[i].is_prime = 1;  //mark all numbers as prime, in the future we will "delete" them
    }

    start = omp_get_wtime();

    struct starter_pack pack = sieve_of_Eratosthenes(numbers, sqrt_N); // creating a pack of prime numbers to work with
                                                                       // in further parallel algorithm

#pragma omp parallel shared(N, pack, sqrt_N, numbers) default (none)
    {
#pragma omp  for schedule(guided)
        for (int i = sqrt_N; i < N; i++) { // checking rest of numbers in parallel
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
    free(numbers);
    free(pack.prime_nums);
    return 0;
}

struct starter_pack sieve_of_Eratosthenes(struct number * numbers, int size){
    struct starter_pack res;
    res.size = 0;
    for (int i = 0; i < size; ++i) { // sieve of Eratosthenes
        if(numbers[i].is_prime){
            res.size++;
            for (int j = i + numbers[i].value; j < size; j += numbers[i].value) {
                numbers[j].is_prime = 0;
            }
        }
    }

    res.prime_nums = malloc(res.size * sizeof(int));
    int j = 0;
    for (int i = 0; i < size; ++i) { // collecting prime numbers
        if(numbers[i].is_prime){
            res.prime_nums[j] = numbers[i].value;
            j++;
        }
    }
    return res;
}

int is_not_prime(int x, struct starter_pack pack){ // returns 0 if x is prime according to the pack
    for (int i = 0; i < pack.size; ++i) {          // else returns 1
        if (x % pack.prime_nums[i] == 0){
            return 1;
        }
    }
    return 0;
}
