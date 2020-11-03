//
// Created by Ilya on 03.11.2020.
//

#ifndef TASK8_ALL_H
#define TASK8_ALL_H

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define T_NUM 2

struct ArrayList {
    int * array;
    int len;
    int mem_len;
} typedef ArrayList;

struct Task {
    int start;
    int end;
    struct Task * next;
} typedef Task;

struct Stack{
    int len;
    Task * first;
} typedef Stack;

void add(ArrayList * list,int x);
ArrayList arrayListCreate();
void copy(ArrayList * from, ArrayList * to);

void q_sort(ArrayList * list);
void quicksort(ArrayList * list, int start, int end);
void par_q_sort(ArrayList * list);
void par_quicksort(ArrayList * list, int start, int end);
int partition(ArrayList * list, int start, int end);
void swap(int * a, int * b);
void printList(ArrayList * list);
void fprintList(FILE * file, ArrayList * list);
void checkList(ArrayList * list);
void generateInput(char* file_name, int n);
void scanInput(FILE * input, ArrayList * list);
void setInputOutput(int argc, char *argv[], FILE ** input, FILE ** output);

#endif //TASK8_ALL_H
