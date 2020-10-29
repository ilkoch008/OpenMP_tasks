#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#define T_NUM 4
#define N 100 // number of iterations 
#define HEIGHT 200
#define WIDTH 400

int main() {
    printf("Hello, World!\n");
    float ** field = malloc(HEIGHT * sizeof(float*));
    for (int i = 0; i < HEIGHT; ++i) {
        field[i] = malloc(WIDTH * sizeof(float));
        for (int j = 0; j < WIDTH; ++j) {
            field[i][j] = 0;
        }
    }
    float ** field_backup = malloc(HEIGHT * sizeof(float*));
    for (int i = 0; i < HEIGHT; ++i) {
        field_backup[i] = malloc(WIDTH * sizeof(float));
    }

    for (int i = 0; i < HEIGHT; ++i) {
        field[i][0] = 100;
        field[i][WIDTH-1] = 100;
    }
    for (int i = 0; i < WIDTH; ++i) {
        field[HEIGHT-1][i] = 100;
    }

#pragma omp parallel shared(field, field_backup) default (none)
    {
#pragma omp  for schedule(guided) // from left to right
        for (int i = 1; i < HEIGHT-1; i++) {
            for (int j = 1; j < WIDTH-1; j++) {
                field_backup[i][j] = (field[i+1][j]+field[i-1][j]+field[i][j+1]+field[i][j-1])* (float) 0.25;
            }
        }
#pragma omp  for schedule(guided) // from right to left
        for (int i = 1; i < HEIGHT-1; i++) {
            for (int j = 1; j < WIDTH - 1; j++) {
                field_backup[i][WIDTH - 1 - j] =
                        (field[i + 1][WIDTH - 1 - j] + field[i - 1][WIDTH - 1 - j] + field[i][WIDTH - 1 - j + 1] +
                         field[i][WIDTH - 1 - j - 1]) * (float) 0.25;
            }
        }
#pragma omp  for schedule(guided) // from top to bottom
        for (int i = 1; i < HEIGHT-1; i++) {
            for (int j = 1; j < WIDTH-1; j++) {
                field_backup[i][j] = (field[i+1][j]+field[i-1][j]+field[i][j+1]+field[i][j-1])* (float) 0.25;
            }
        }
#pragma omp  for schedule(guided) // from bottom to top
        for (int i = 1; i < HEIGHT-1; i++) {
            for (int j = 1; j < WIDTH-1; j++) {
                field_backup[i][j] = (field[i+1][j]+field[i-1][j]+field[i][j+1]+field[i][j-1])* (float) 0.25;
            }
        }
    }
    return 0;
}
