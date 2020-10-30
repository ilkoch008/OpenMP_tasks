#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <string.h>

struct temperature{
    int r;
    int g;
    int b;
};

struct temperature convert(float temperature); // converts temperature to rgb
void iteration(float ** field, float ** field_backup); // calculation of next state

int FPD = 100; // frames per drawing
int HEIGHT = 400; // size of field
int WIDTH = 800;
int T_NUM = 4; // num of threads

int main(int argc, char *argv[]) {

    char * end_ptr;
    for (int i = 0; i < argc; ++i) {
        if (strstr(argv[i], "res") != NULL){
            WIDTH = strtol(argv[i+1], &end_ptr, 10);
            HEIGHT = strtol(argv[i+2], &end_ptr, 10);
        } else if (strstr(argv[i], "fpd") != NULL){
            FPD = strtol(argv[i+1], &end_ptr, 10);
        } else if (strstr(argv[i], "tnum") != NULL){
            T_NUM = strtol(argv[i+1], &end_ptr, 10);
        }
    }

    omp_set_num_threads(T_NUM);

    //=============================== for drawing
    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        return 1;
    }
    SDL_Surface* screen_surface = NULL;
    SDL_Window* window = NULL;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
    screen_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 255, 255, 255));
    struct temperature temp = convert(0);
    SDL_SetRenderDrawColor(renderer, temp.r, temp.g, temp.b, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    //====================================================================

    //========= initializing of two fields
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

    for (int i = 0; i < WIDTH; ++i) {
        field[HEIGHT-1][i] = 100;
    }
    for (int i = 0; i < HEIGHT; ++i) {
        field[i][0] = 100;
        field[i][WIDTH-1] = 100;
    }
    //=================================================================

    int k = 0;
    int kk = 0;
    double end, start, res;
    double  fps;
    char str[40] = "fps: ";
    char fps_str[20];

    while (1) { // computing in cycle
        iteration(field, field_backup);
        if(kk == FPD) {
            for (int i = 0; i < HEIGHT; ++i) {
                for (int j = 0; j < WIDTH; ++j) {
                    temp = convert(field[i][j]);
                    SDL_SetRenderDrawColor(renderer, temp.r, temp.g, temp.b, 255);
                    SDL_RenderDrawPoint(renderer, j, i);
                }
            }
            SDL_RenderPresent(renderer);
            kk = 0;
        }
        k++;
        kk++;
        if(k==10){
            k = 0;
            end = omp_get_wtime();
            res = end - start;
            fps = 10/res;
            gcvt (fps, 4, fps_str);
            strcpy(str+5, fps_str);
            SDL_SetWindowTitle(window, str);
            start = omp_get_wtime();
        }
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    for (int i = 0; i < HEIGHT; ++i) {
        free(field[i]);
    }
    for (int i = 0; i < HEIGHT; ++i) {
        free(field_backup[i]);
    }

    free(field_backup);
    free(field);

    return 0;
}

struct temperature convert(float temperature){
    struct temperature result;
    if(temperature > 50){
        result.b = 0;
        result.r = (int) (255 * 0.5*(1 + cosf(M_PI/50*temperature)));
    } else {
        result.r = 0;
        result.b = (int) (255 * 0.5*(1 + cosf(M_PI/50*temperature)));
    }
    result.g = (int) (255 * 0.5*(1 + cosf(M_PI/50*temperature + M_PI)));
    return result;
}

void iteration(float ** field, float ** field_backup){ // calculates average of neighbors temperature for each cell
                                                       // in different directions
#pragma omp parallel shared(field, field_backup, HEIGHT, WIDTH) default (none)
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
                field[i][WIDTH - 1 - j] =
                        (field_backup[i + 1][WIDTH - 1 - j] + field_backup[i - 1][WIDTH - 1 - j] +
                         field_backup[i][WIDTH - 1 - j + 1] +
                         field_backup[i][WIDTH - 1 - j - 1]) * (float) 0.25;
            }
        }
#pragma omp  for schedule(guided) // from top to bottom
        for (int j = 1; j < WIDTH-1; j++) {
            for (int i = 1; i < HEIGHT-1; i++) {
                field_backup[i][j] = (field[i+1][j]+field[i-1][j]+field[i][j+1]+field[i][j-1])* (float) 0.25;
            }
        }
#pragma omp  for schedule(guided) // from bottom to top
        for (int j = 1; j < WIDTH-1; j++) {
            for (int i = 1; i < HEIGHT - 1; i++) {
                field[HEIGHT - 1 - i][j] =
                        (field_backup[HEIGHT - 1 - i + 1][j] + field_backup[HEIGHT - 1 - i - 1][j] +
                         field_backup[HEIGHT - 1 - i][j + 1] +
                         field_backup[HEIGHT - 1 - i][j - 1]) * (float) 0.25;
            }
        }
    }
}
