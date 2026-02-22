#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LENGTH 100
#define LOOP_AMOUNT 1000 * 1000 * 1000
#define ACCESS_INDEX 5

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

int main() {
    clock_t begin = clock();

    // initialize array and linked list
    int *arr = (int*) malloc(sizeof(int) * ARRAY_LENGTH);
    ListNode *list = (ListNode*) malloc(sizeof(ListNode));

    // initialize value of both linked list and array

    ListNode *list_arr[4] = {list, list, list, list};
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        arr[i] = i;
    }
    list->value = 0;
    ListNode *current_node = list;
    for (int i = 0; i < ARRAY_LENGTH-1; i++) {
        ListNode *new_node = (ListNode*) malloc(sizeof(ListNode));
        new_node->value = i + 1;
        current_node->next = new_node;
        current_node = new_node;
    }

    clock_t end = clock();
    double total_time = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("initialization time: %f\n", total_time);


    printf("Testing element access time of index %d with %d loops\n", ACCESS_INDEX, LOOP_AMOUNT);

    // test array access time
    begin = clock();
    int value_arr = 0;
    for (int i = 0; i < LOOP_AMOUNT; i++) {
        value_arr = arr[ACCESS_INDEX];
    }
    end = clock();
    total_time = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("Array access time: %f seconds\n", total_time);

    // test linked list access time
    begin = clock();
    int value_linked_list = 0;
    for (int i = 0; i < LOOP_AMOUNT; i++) {
        current_node = list_arr[3];
        for (int j = 0; j < ACCESS_INDEX-1; j++) {
            value_linked_list = current_node->value;
            current_node = current_node->next;    
        }
    }
    end = clock();
    total_time = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("Linked list access time: %f seconds\n", total_time);

    // free memory (later)
    free(arr);
    current_node = list;
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        ListNode *free_node = current_node;
        current_node = current_node->next;
        free(free_node);
    }
}
