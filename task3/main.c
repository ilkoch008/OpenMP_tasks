#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define T_NUM 2
#define SIZE 15

int main() {
    omp_set_num_threads(T_NUM);
    unsigned long long int *a = malloc(SIZE * sizeof(unsigned long long int));
    unsigned long long int save;
    for (int i = 0; i < SIZE; i++) {
        a[i] = (unsigned long long int) i;
    }

    printf("original array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%lld ", a[i]);
    }
    printf("\n");

    omp_lock_t simple_lock;
    omp_init_lock(&simple_lock);
    int check;
    double end, start = omp_get_wtime();
    save = a[SIZE-1];

#pragma omp parallel shared(a, simple_lock, check) default (none)
    {
        int id = omp_get_thread_num();
        int first_it = 2;
        unsigned long long int buff1, buff2, buff3;
        int num_of_p = omp_get_num_threads();
#pragma omp master
        {
            check = num_of_p - 1;
        }
#pragma omp  for schedule(static)
        for (int i = 2; i < SIZE; i++) {
            if (first_it) {
                while (1) { // synchronizing two first cycles in the same way as in first task
                            // (computing first and second steps from last process to first)
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
                        if(check != 0){
                            check--;
                        } else { // cocking the counter on the zero thread
                            check = num_of_p - 1;
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
    for (int i = 1; i < SIZE-1; ++i) {
        a[i] = a[i+1];
    }
    a[SIZE-1] = save;
    double time = end - start;

    printf("calculated array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%lld ", a[i]);
    }
    printf("\n");
    printf("execution time: %f\n", time);
    free(a);
    omp_destroy_lock(&simple_lock);
    return 0;
}
