//
// Created by Ilya on 20.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#define ISIZE 1000
#define JSIZE 1000
#define TAG_STOP 1
#define TAG_PLACE 2
#define TAG_ARRAY 3

void compute_cycle_master(double ** a, int world_size);
void compute_first_cycle_slave(double * a_i);
void compute_second_cycle_slave(double * a_i);
void compute_two_cycles_slave(double * a_i);
void print_ff(FILE * ff, double ** a);
void compute_solo(double ** a);

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int my_rank;
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int i, j;

    if(my_rank == 0) {
        if (world_size < 2) {
            fprintf(stderr, "Error: number of processes must be two or more.\n");
            exit(-1);
        }
    }

    if(my_rank == 0){
        double ** a = malloc(ISIZE * sizeof(double *));
        for (i=0; i<ISIZE; i++) {
            a[i] = malloc(JSIZE * sizeof(double));
        }
        double start, end, res;
        start = MPI_Wtime();
        compute_cycle_master(a, world_size);
        compute_cycle_master(a, world_size);
        end = MPI_Wtime();
        res = end - start;
        printf("time without changing graph: %0.16f\n", res);

        start = MPI_Wtime();
        compute_cycle_master(a, world_size);
        end = MPI_Wtime();
        res = end - start;
        printf("time with changing graph: %0.16f\n", res);

        FILE *ff;
        ff = fopen("result.txt", "w");
        print_ff(ff, a);
        fclose(ff);

        for (i=0; i<ISIZE; i++) {
            free(a[i]);
        }
        free(a);

    } else {
        double * a_i = malloc(JSIZE * sizeof(double));
        compute_first_cycle_slave(a_i);
        compute_second_cycle_slave(a_i);
        compute_two_cycles_slave(a_i);
        free(a_i);
    }
    if(my_rank == 0) {
        double **a = malloc(ISIZE * sizeof(double *));
        for (i = 0; i < ISIZE; i++) {
            a[i] = malloc(JSIZE * sizeof(double));
        }
        double start, end, res;
        start = MPI_Wtime();
        compute_solo(a);
        end = MPI_Wtime();
        res = end - start;
        printf("time solo: %0.16f\n", res);
        for (i=0; i<ISIZE; i++) {
            free(a[i]);
        }
        free(a);
    }



    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}


void compute_cycle_master(double ** a, int world_size){
    int place, i;
    MPI_Status  status;


    for (i=0; i<world_size-1; i++){
        MPI_Send(&i, 1, MPI_INT, i+1, TAG_PLACE, MPI_COMM_WORLD);
        MPI_Send(a[i], JSIZE, MPI_DOUBLE, i+1, TAG_ARRAY, MPI_COMM_WORLD);
    }

    for (i=world_size-1; i<ISIZE; i++) {
        MPI_Recv(&place, 1, MPI_INT, MPI_ANY_SOURCE, TAG_PLACE, MPI_COMM_WORLD, &status);
        MPI_Recv(a[place], JSIZE, MPI_DOUBLE, status.MPI_SOURCE, TAG_ARRAY, MPI_COMM_WORLD, &status);
        MPI_Send(&i, 1, MPI_INT, status.MPI_SOURCE, TAG_PLACE, MPI_COMM_WORLD);
        MPI_Send(a[i], JSIZE, MPI_DOUBLE, status.MPI_SOURCE, TAG_ARRAY, MPI_COMM_WORLD);
    }

    for (i=0; i<world_size-1; i++){
        MPI_Recv (&place, 1, MPI_INT, MPI_ANY_SOURCE, TAG_PLACE, MPI_COMM_WORLD, &status);
        MPI_Recv (a[place], JSIZE, MPI_DOUBLE, status.MPI_SOURCE, TAG_ARRAY, MPI_COMM_WORLD, &status);
        MPI_Send(&place, 1, MPI_INT, status.MPI_SOURCE, TAG_STOP, MPI_COMM_WORLD);
    }
}
void compute_first_cycle_slave(double * a_i){
    int place, j;
    MPI_Status  status;
    while(1){
        MPI_Recv (&place, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if(status.MPI_TAG == TAG_STOP){
            break;
        }
        MPI_Recv (a_i, JSIZE, MPI_DOUBLE, 0, TAG_ARRAY, MPI_COMM_WORLD, &status);
        for (j=0; j<JSIZE; j++){
            a_i[j] = 10*place +j;
        }
        MPI_Send(&place, 1, MPI_INT, 0, TAG_PLACE, MPI_COMM_WORLD);
        MPI_Send(a_i, JSIZE, MPI_DOUBLE, 0, TAG_ARRAY, MPI_COMM_WORLD);
    }
}

void compute_second_cycle_slave(double * a_i){
    int place, j;
    MPI_Status  status;
    while(1){
        MPI_Recv (&place, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if(status.MPI_TAG == TAG_STOP){
            break;
        }
        MPI_Recv (a_i, JSIZE, MPI_DOUBLE, 0, TAG_ARRAY, MPI_COMM_WORLD, &status);
        for (j=0; j<JSIZE; j++){
            a_i[j] = sin(0.00001*a_i[j]);
        }
        MPI_Send(&place, 1, MPI_INT, 0, TAG_PLACE, MPI_COMM_WORLD);
        MPI_Send(a_i, JSIZE, MPI_DOUBLE, 0, TAG_ARRAY, MPI_COMM_WORLD);
    }
}

void compute_two_cycles_slave(double * a_i){
    int place, j;
    MPI_Status  status;
    while(1){
        MPI_Recv (&place, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if(status.MPI_TAG == TAG_STOP){
            break;
        }
        MPI_Recv (a_i, JSIZE, MPI_DOUBLE, 0, TAG_ARRAY, MPI_COMM_WORLD, &status);
        for (j=0; j<JSIZE; j++){
            a_i[j] = sin(0.00001*(10*place +j));
        }
        MPI_Send(&place, 1, MPI_INT, 0, TAG_PLACE, MPI_COMM_WORLD);
        MPI_Send(a_i, JSIZE, MPI_DOUBLE, 0, TAG_ARRAY, MPI_COMM_WORLD);
    }
}

void print_ff(FILE * ff, double ** a){
    int i, j;
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            fprintf(ff, "%f ", a[i][j]);
        }
        fprintf(ff, "\n");
    }
}

void compute_solo(double ** a) {
    int i, j;
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
    }
    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = sin(0.00001 * a[i][j]);
        }
    }
}
