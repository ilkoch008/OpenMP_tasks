#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define T_NUM 2
#define SIZE 100000

int main() {
    omp_set_num_threads(T_NUM);
    unsigned long long int *a = malloc(SIZE * sizeof(unsigned long long int));
    for (int i = 0; i < SIZE; i++) {
        a[i] = (unsigned long long int) i;
    }
    omp_lock_t simple_lock;
    omp_init_lock(&simple_lock);
    int check = 0;
    double end, start = omp_get_wtime();

#pragma omp parallel shared(a, simple_lock, check) default (none)
    {
        int id = omp_get_thread_num();
        int first_it = 2;
        unsigned long long int buff1, buff2, buff3;
        int num_of_p = omp_get_num_threads();
#pragma omp  for schedule(static)
        for (int i = 2; i < SIZE; i++) {
            if (first_it) {
                while (1) { // synchronizing two first cycles in the same way as in first task
                            // (computing first and second steps from first process to last)
                    if (id == check) {
                        omp_set_lock(&simple_lock);
                        if (first_it == 2) {
                            buff3 = a[i - 2];
                            buff2 = a[i - 1];
                            buff1 = a[i];
                            a[i] = buff3 * buff2 * buff1 / 3;
                            first_it--;
                        } else {
                            buff3 = buff2;
                            buff2 = buff1;
                            buff1 = a[i];
                            a[i] = buff3 * buff2 * buff1 / 3;
                            first_it--;
                        }
                        if(check != num_of_p - 1){
                            check++;
                        } else {
                            check = 0;
                        }
                        omp_unset_lock(&simple_lock);
                        break;
                    }
                }
            } else { // computing for other steps
                buff3 = buff2;
                buff2 = buff1;
                buff1 = a[i];
                a[i] = buff3 * buff2 * buff1 / 3;
            }
        }
    }

    end = omp_get_wtime();
    double time = end - start;

    for (int i = 0; i < SIZE; i++) {
        printf("%lld ", a[i]);
    }
    printf("\n");
    printf("execution time: %f\n", time);
    free(a);
    omp_destroy_lock(&simple_lock);
    return 0;
}
