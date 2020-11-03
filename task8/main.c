#include "all.h"

int OUT_IN_FILE=0;
int IN_FROM_FILE=0;

int main(int argc, char *argv[]) {
    FILE * input;
    FILE * output;
    omp_set_num_threads(T_NUM);
    double start1, end1, time1;
    double start2, end2, time2;
    //generateInput("input.txt", 300000);
    setInputOutput(argc, argv, &input, &output);
    ArrayList list = arrayListCreate();
    ArrayList list1 = arrayListCreate();

    scanInput(input, &list);
    copy(&list, &list1);

    start1 = omp_get_wtime();
    q_sort(&list);
    end1 = omp_get_wtime();
    time1 = end1 - start1;

    start2 = omp_get_wtime();
    par_q_sort(&list1);
    end2 = omp_get_wtime();
    time2 = end2 - start2;

    printf("q_sort time: %f\npar_q_sort time: %f\n", time1, time2);
    checkList(&list);
    checkList(&list1);
    fprintList(output, &list1);
    if(IN_FROM_FILE)
        fclose(input);
    if(OUT_IN_FILE)
        fclose(output);
    free(list.array);
    return 0;
}

void add(ArrayList * list,int x){
    if(list->array == NULL){
        list->array = malloc(100 * sizeof(int));
        list->len = 0;
        list->mem_len = 100;
    }
    if(list->len == list->mem_len){
        list->array = realloc(list->array, sizeof(int) * (100 + list->mem_len));
        list->mem_len += 100;
    }
    list->array[list->len] = x;
    list->len++;
}

ArrayList arrayListCreate(){
    ArrayList list;
    list.array = NULL;
    list.len = 0;
    list.mem_len = 0;
    return list;
}

void copy(ArrayList * from, ArrayList * to){
    for (int i = 0; i < from->len; ++i) {
        add(to, from->array[i]);
    }
}

int partition(ArrayList * list, int start, int end){

    int med;
    int med_pos;
    int mid = (start + end)/2;

    if(start == end){
        return start;
    } else {
        if (list->array[start] <= list->array[mid] && list->array[mid] <= list->array[end]){ // choosing support element ===
            med = list->array[mid];
            med_pos = mid;
        } else if (list->array[mid] <= list->array[start] && list->array[start] <= list->array[end]){
            med = list->array[start];
            med_pos = start;
        } else {
            med = list->array[end];
            med_pos = end;
        } // ===========================================================================================================

        swap(&list->array[med_pos], &list->array[end]);
        med_pos = end;

//        med = list->array[end];
//        med_pos = end;

        for (int i = start; i <= end; i++) {
            if(list->array[i] > med){
                for (int j = end-1; j >= i; j--) {
                    if (i == j){
                        swap(&list->array[i], &list->array[med_pos]);
                        return j;
                    }
                    if(list->array[j] <= med){
                        swap(&list->array[i], &list->array[j]);
                        break;
                    }
                }
            }
        }
    }
    return med_pos;
}

void quicksort(ArrayList * list, int start, int end) { // recursive algorithm, taken from wikipedia
    if (start < end) {
        int med = partition(list, start, end);
        quicksort(list, start, med - 1);
        quicksort(list, med + 1, end);
    }
}

void q_sort(ArrayList * list) {
    if(list->len != 0 && list->len != 1) {
        quicksort(list, 0, list->len - 1);
    }
}

void swap(int *a, int * b){
    int save = *a;
    (*a) = *b;
    (*b) = save;
}

void printList(ArrayList * list){
    for (int i = 0; i < list->len; ++i) {
        printf("%d ", list->array[i]);
    }
    printf("\n");
    fflush(stdout);
}

void fprintList(FILE * file, ArrayList * list){
    for (int i = 0; i < list->len; ++i) {
        fprintf(file,"%d\n", list->array[i]);
    }
    //fprintf(file,"\n");
}

void checkList(ArrayList * list){
    for (int i = 0; i < list->len - 1; ++i) {
        if(list->array[i] > list->array[i+1]){
            fprintf(stderr, "AHTUNG for i = %d\n", i);
        }
    }
}

void generateInput(char * file_name, int n){
    FILE * input = fopen(file_name, "w");
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        fprintf(input, "%d ", rand());
    }
    fclose(input);
}

void scanInput(FILE * input, ArrayList * list){
    int scan;
    while(fscanf(input, "%d", &scan) == 1){
        add(list, scan);
    }
}

void setInputOutput(int argc, char *argv[], FILE ** input, FILE ** output){
    char * end_ptr;
    *input = stdin;
    *output = stdout;
    for (int i = 0; i < argc; ++i) {
        if (strstr(argv[i], "-i") != NULL){
            *input = fopen(argv[i+1], "r");
            IN_FROM_FILE = 1;
            i++;
        } else if (strstr(argv[i], "-o") != NULL){
            *output = fopen(argv[i+1], "w");
            OUT_IN_FILE = 1;
            i++;
        }
    }
}

void par_q_sort(ArrayList * list){
    if(list->len != 0 && list->len != 1) {
        par_quicksort(list, 0, list->len - 1);
    }
}

void par_quicksort(ArrayList *list, int start, int end) {

    int med0 = partition(list, start, end);
    int med1, med2;


#pragma omp parallel shared(med0, med1, med2, list, start, end) default (none)
    {
#pragma omp sections
        {
#pragma omp section
            {
                med1 = partition(list, start, med0 - 1);
            }
#pragma omp section
            {
                med2 = partition(list, med0 + 1, end);
            }
        }
#pragma omp barrier
    }

#pragma omp parallel shared(med0, med1, med2, list, start, end) default (none)
    {
#pragma omp sections
        {
#pragma omp section
            {
                quicksort(list, start, med1-1);
            }
#pragma omp section
            {
                quicksort(list, med1+1, med0-1);
            }
#pragma omp section
            {
                quicksort(list, med0+1, med2-1);
            }
#pragma omp section
            {
                quicksort(list, med2+1, end);
            }
        }
    }
}
