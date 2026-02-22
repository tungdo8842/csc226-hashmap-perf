#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LENGTH 100
#define LOOP_AMOUNT 100 * 1000 * 1000
#define PROBE_COUNT 20

int main() {
    clock_t begin = clock();

    // initialize array and value
    int *arr = (int*) malloc(sizeof(int) * ARRAY_LENGTH);
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        arr[i] = i;
    }
    clock_t end = clock();
    double total_time = (double)(end-begin) / CLOCKS_PER_SEC;
    // printf("initialization time: %f\n", total_time);


    printf("Testing array element probing %d times with %d loops\n", PROBE_COUNT, LOOP_AMOUNT);

    begin = clock();
    int value_arr = 0;
    for (int i = 0; i < LOOP_AMOUNT; i++) {
        int index = 0;
        for (int j = 0; j < PROBE_COUNT; j++) {
            index = (index + 1) % ARRAY_LENGTH;
            value_arr = arr[index];
        }
    }
    end = clock();
    total_time = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("Array access time with simulated probing: %f seconds\n", total_time);

    begin = clock();
    value_arr = 0;
    for (int i = 0; i < LOOP_AMOUNT; i++) {
        value_arr = arr[67];
    }
    end = clock();
    total_time = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("Array access without probing: %f seconds\n", total_time);
    // free memory
    free(arr);
}
