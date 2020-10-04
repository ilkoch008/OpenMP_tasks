#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#define SIZE 1500
#define T_NUM 10

void matrixMult_def(double ** matrixA, double ** matrixB, double ** matrixC, int size);
void matrixMult_stat_str(double ** matrixA, double ** matrixB, double ** matrixC, int size);
void matrixMult_dyn_str(double ** matrixA, double ** matrixB, double ** matrixC, int size);
void matrixMult_guided_str(double ** matrixA, double ** matrixB, double ** matrixC, int size);
void matrixMult_static_all(double ** matrixA, double ** matrixB, double ** matrixC, int size);
void matrixMult_dyn_all(double ** matrixA, double ** matrixB, double ** matrixC, int size);
void matrixMult_guided_all(double ** matrixA, double ** matrixB, double ** matrixC, int size);
double ** matrixInit(int size);
void matrixDestroy(void ** matrix, int size);

int main() {
    omp_set_num_threads(T_NUM);
    double end, start, res;
    double ** matrixA = matrixInit(SIZE);
    double ** matrixB = matrixInit(SIZE);
    double ** matrixC = matrixInit(SIZE);


    start = omp_get_wtime();
    matrixMult_def(matrixA, matrixB, matrixC, SIZE);
    end = omp_get_wtime();
    res = end - start;
    printf("execution time for def: %f\n", res);

//    start = omp_get_wtime();
//    matrixMult_stat_str(matrixA, matrixB, matrixC, SIZE);
//    end = omp_get_wtime();
//    res = end - start;
//    printf("execution time for stat_str: %f\n", res);
//
//    start = omp_get_wtime();
//    matrixMult_dyn_str(matrixA, matrixB, matrixC, SIZE);
//    end = omp_get_wtime();
//    res = end - start;
//    printf("execution time for dyn_str: %f\n", res);
//
//    start = omp_get_wtime();
//    matrixMult_guided_str(matrixA, matrixB, matrixC, SIZE);
//    end = omp_get_wtime();
//    res = end - start;
//    printf("execution time for guided_str: %f\n", res);
//
//    start = omp_get_wtime();
//    matrixMult_static_all(matrixA, matrixB, matrixC, SIZE);
//    end = omp_get_wtime();
//    res = end - start;
//    printf("execution time for static_all: %f\n", res);
//
//    start = omp_get_wtime();
//    matrixMult_dyn_all(matrixA, matrixB, matrixC, SIZE);
//    end = omp_get_wtime();
//    res = end - start;
//    printf("execution time for dyn_all: %f\n", res);
//
//    start = omp_get_wtime();
//    matrixMult_guided_all(matrixA, matrixB, matrixC, SIZE);
//    end = omp_get_wtime();
//    res = end - start;
//    printf("execution time for guided_all: %f\n", res);

    matrixDestroy((void **) matrixA, SIZE);
    matrixDestroy((void **) matrixB, SIZE);
    matrixDestroy((void **) matrixC, SIZE);
    return 0;
}


double ** matrixInit(int size){
    double ** matrix = malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++) {
        matrix[i] = malloc(size * sizeof(double));
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = omp_get_wtime();
        }
    }
    return matrix;
}

void matrixDestroy(void ** matrix, int size){
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void matrixMult_def(double ** matrixA, double ** matrixB, double ** matrixC, int size){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrixC[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void matrixMult_stat_str(double ** matrixA, double ** matrixB, double ** matrixC, int size){
#pragma omp parallel shared(matrixA, matrixB, matrixC, size) default (none)
    {
#pragma omp  for schedule(static)
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrixC[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
#pragma omp barrier
    }
}

void matrixMult_dyn_str(double ** matrixA, double ** matrixB, double ** matrixC, int size){
#pragma omp parallel shared(matrixA, matrixB, matrixC, size) default (none)
    {
#pragma omp  for schedule(dynamic)
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrixC[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
#pragma omp barrier
    }
}

void matrixMult_guided_str(double ** matrixA, double ** matrixB, double ** matrixC, int size){
#pragma omp parallel shared(matrixA, matrixB, matrixC, size) default (none)
    {
#pragma omp  for schedule(guided)
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrixC[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
#pragma omp barrier
    }
}

void matrixMult_static_all(double ** matrixA, double ** matrixB, double ** matrixC, int size){
    int size_2 = size * size;
#pragma omp parallel shared(matrixA, matrixB, matrixC, size, size_2) default (none)
    {
        int i=0, j=0;
#pragma omp  for schedule(static)
        for (int m = 0; m < size_2; ++m) {
            i = m / size;
            j = m % size;
            matrixC[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
#pragma omp barrier
    }
}

void matrixMult_dyn_all(double ** matrixA, double ** matrixB, double ** matrixC, int size){
    int size_2 = size * size;
#pragma omp parallel shared(matrixA, matrixB, matrixC, size, size_2) default (none)
    {
        int i=0, j=0;
#pragma omp  for schedule(dynamic)
        for (int m = 0; m < size_2; ++m) {
            i = m / size;
            j = m % size;
            matrixC[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
#pragma omp barrier
    }
}

void matrixMult_guided_all(double ** matrixA, double ** matrixB, double ** matrixC, int size){
    int size_2 = size * size;
#pragma omp parallel shared(matrixA, matrixB, matrixC, size, size_2) default (none)
    {
        int i=0, j=0;
#pragma omp  for schedule(guided)
        for (int m = 0; m < size_2; ++m) {
            i = m / size;
            j = m % size;
            matrixC[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
#pragma omp barrier
    }
}

void matrixMult_stat_wtf(double ** matrixA, double ** matrixB, double ** matrixC, int size){
#pragma omp parallel shared(matrixA, matrixB, matrixC, size) default (none)
    {
#pragma omp  for schedule(static)
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrixC[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
#pragma omp barrier
    }
}