#include <stdio.h>
#include <omp.h>
#define T_NUM 10

int main() {
    omp_set_num_threads(T_NUM);
    int id;
    int check = T_NUM - 1;
    omp_lock_t lock;
    omp_init_lock(&lock);
#pragma omp parallel shared(check, lock) private(id) default (none)
    {
        id = omp_get_thread_num();
        while (1) {
            if(id == check) {
                omp_set_lock(&lock);
                check--;
                printf("Hello, World! My id is %d.\n", id);
                fflush(stdout);
                break;
            }
        }
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
    return 0;
}
