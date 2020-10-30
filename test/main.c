#include <stdio.h>
#include <omp.h>

int main() {

    int a = 0;
#pragma omp parallel num_threads(4)
    for (int i = 0; i < 5; i++)
        a += i;

    printf ("%d\n", a);

    return 0;
}
