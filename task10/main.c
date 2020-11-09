#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include <process.h>
#include <string.h>

#define T_NUM 3

//#define N 16777216 // = 2^24
//#define POW 24
//#define h 0.0000011920928955078125 // = 20/2^24

//#define N 1048576 // = 2^20
//#define POW 20
//#define h 0.000019073486328125 // = 20/2^20

#define N 4194304 // = 2^22
#define POW 22
#define h 0.00000476837158203125 // = 20/2^22


void setOnes(long double * array);
void mul(long double * array, long double num);
long double * compute_b(long double * result, const long double * Y);
long double * compute_g(long double * result, const long double * Y);
long double * solveTriDiag(long double * a, long double * b, long double * c, long double * Y, long double * g);

long double get_diff(const long double * Y_1, const long double * Y_2);
long double check_sum(const long double * Y);

void print_array(char * file_name, long double * array, int size);
void print_x(char * file_name, int size);

long double a_const = 100;

int main(int argc, char *argv[]) {
    long double * Y = malloc((N+1) * sizeof(long double));
    long double * Y_next = malloc((N+1) * sizeof(long double));
    long double * a = malloc((N+1) * sizeof(long double));
    long double * b = malloc((N+1) * sizeof(long double));
    long double * c = malloc((N+1) * sizeof(long double));
    long double * g = malloc((N+1) * sizeof(long double));
    long double sqrt_2 = sqrt(2);

    for (int i = 0; i < N+1; ++i) {
        Y[i] = 0;
        Y_next[i] = 0;
        a[i] = 1;
        c[i] = 1;
    }

    Y[0] = 0.997;
    Y[N] = 0.997;
    Y_next[0] = 0.997;
    Y_next[N] = 0.997;

    //=========================================================================
    long double * save;
    double diff = 100;
    double check1, check2 = 100;
    double check_best = 10000;
    double check_best_a;
    int i = 0;

        while (i < 2) {
            compute_b(b, Y);
            compute_g(g, Y);
            setOnes(a);
            setOnes(c);
            solveTriDiag(a, b, c, Y_next, g);
            check2 = (double) check_sum(Y_next);
            check1 = (double) check_sum(Y);
            diff = check1 - check2;
            save = Y;
            Y = Y_next;
            Y_next = save;
            printf("iteration %d, check: %0.16lf, diff: %0.16lf\n", i, check1, diff);
            fflush(stdout);
            i++;
        }

    //=========================================================================
    print_array("Y.txt", Y_next, N+1);
    print_x("x.txt", N+1);
    execl("python", "build_graph.py");
    free(Y);
    free(Y_next);
    free(a);
    free(b);
    free(c);
    free(g);

    return 0;
}

long double * compute_b(long double * result, const long double * Y) {
#pragma omp parallel shared(result, Y, a_const) default (none)
    {
#pragma omp  for schedule(guided)
        for (int i = 1; i < N; i++) {
//            result[i] = -2 - a_const*h*h*(Y[i+1]*Y[i+1] + 10*Y[i]*Y[i] + Y[i-1]*Y[i-1] - 4)/4;
            result[i] = -2 - a_const*h*h*(3*Y[i]*Y[i] - 1);
//            result[i] = -2 - a_const*h*h*(- 1); // for y'' - ay = 0
        }
    }
    return result;
}

long double * compute_g(long double * result, const long double * Y){
#pragma omp parallel shared(result, Y, a_const) default (none)
    {
#pragma omp  for schedule(guided)
        for (int i = 1; i < N; i++) {
//            result[i] = a_const*h*h*(Y[i+1]*Y[i+1]*Y[i+1] - Y[i+1] - 20*Y[i]*Y[i]*Y[i] + 2*Y[i] +
//                    Y[i-1]*Y[i-1]*Y[i-1] - Y[i-1] - 3*Y[i]*Y[i+1]*Y[i+1] - 3*Y[i]*Y[i-1]*Y[i-1])/12;
            result[i] = a_const*h*h*(Y[i+1]*Y[i+1]*Y[i+1] - Y[i+1] - 26*Y[i]*Y[i]*Y[i] + 2*Y[i] +
                    Y[i-1]*Y[i-1]*Y[i-1] - Y[i-1])/12;
//            result[i] = a_const*h*h*(- Y[i+1] + 2*Y[i] - Y[i-1])/12; // for y'' - ay = 0
        }
    }
    return result;
}

long double *solveTriDiag(long double *a, long double *b, long double *c, long double *Y, long double *g) {
    int start = 2;
    int elementsNum = N - 1;
    int step = 1;
    for (int j = 0; j < POW; j++) { // forward
        elementsNum = (elementsNum - 1) / 2;
        int k;
        long double new_a, new_b, new_c, new_g;
#pragma omp parallel for num_threads(T_NUM) private(k,new_a,new_b,new_c,new_g) shared(a,b,c,g,elementsNum,start,step) default(none)
        for (int i = 0; i < elementsNum; i++) {
            k = start * (i + 1);
            new_a = -a[k] * a[k - step] / b[k - step];
            new_b = b[k] - c[k - step] * a[k] / b[k - step] - c[k] * a[k + step] / b[k + step];
            new_c = -c[k] * c[k + step] / b[k + step];
            new_g = g[k] - a[k] * g[k - step] / b[k - step] - c[k] * g[k + step] / b[k - step];
            a[k] = new_a;
            b[k] = new_b;
            c[k] = new_c;
            g[k] = new_g;
        }
#pragma omp barrier

        start = 2 * start;
        step = 2 * step;
    }

    // reverse
    start = N / 2;
    step = start;
    elementsNum = 1;
    for (int j = POW-1; j >= 0 ; j--) {
        int k;
#pragma omp parallel for num_threads(T_NUM) private(k) shared(a, b, c, g, elementsNum, start, step,Y) default(none)
            for (int i = 0; i < elementsNum; i++) {
                k = start * (2*i + 1);
                Y[k] = (g[k] - c[k]*Y[k+step] - a[k]*Y[k-step])/b[k];
            }
#pragma omp barrier

        start = start / 2;
        step = start;
        elementsNum = elementsNum * 2;
    }
    return Y;
}

void setOnes(long double * array){
#pragma omp parallel shared(array) default (none)
    {
#pragma omp  for schedule(guided)
        for (int i = 0; i < N + 1; i++) {
            array[i] = 1;
        }
    }
}

void print_array(char * file_name, long double * array, int size){
    FILE * file = fopen(file_name, "w");
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%0.16lf\n", (double)array[i]);
    }
    fclose(file);
}

void print_x(char * file_name, int size){
    FILE * file = fopen(file_name, "w");
    long double curr_x = -10;
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%0.16lf\n", (double)curr_x);
        curr_x += h;
    }
    fclose(file);
}

void mul(long double * array, long double num){
#pragma omp parallel shared(array, num) default (none)
    {
#pragma omp  for schedule(guided)
        for (int i = 0; i < N+1; i++) {
            array[i] = array[i] * num;
        }
    }
}

long double get_diff(const long double * Y_1, const long double * Y_2){
    long double res=0;
#pragma omp parallel for num_threads(T_NUM) shared(Y_1,Y_2) reduction(+: res) default(none)
    for (int i = 0; i < N+1; i++) {
        res += fabsl(Y_1[i] - Y_2[i]);
    }
    return res;
}

long double check_sum(const long double * Y){
    long double res=0;
#pragma omp parallel for num_threads(T_NUM) shared(Y,a_const) reduction(+: res) default(none)
    for (int i = 1; i < N; i++) {
        res += fabsl(h*((Y[i+1]-2*Y[i]+Y[i-1])/(h*h) - a_const*(Y[i]*Y[i]*Y[i] - Y[i])));
//        res += fabsl(h*((Y[i+1]-2*Y[i]+Y[i-1])/(h*h) - a_const*(- Y[i])));
    }
    return res;
}
