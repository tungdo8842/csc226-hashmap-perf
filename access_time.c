#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

int main() {
    clock_t begin = clock();
    // initialize array and linked list
    const int arr_length = 1000 * 1000;
    int *arr = (int*) malloc(sizeof(int) * arr_length);

    // initialize linked list and value of both linked list and array
    ListNode *list = (ListNode*) malloc(sizeof(ListNode));
    list->value = 67;
    printf("first node value: %d\n", list->value);
    ListNode *current_node = list;

    for (int i = 0; i < arr_length; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < arr_length-1; i++) {
        ListNode *new_node = (ListNode*) malloc(sizeof(ListNode));
        new_node->value = i;
        current_node->next = new_node;
        current_node = new_node;
    }

    clock_t end = clock();
    double total_time = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("initialization time: %f\n", total_time);

    // testing access time
    int access_index = 10000;

    // test array access time
    begin = clock();
    int value_arr = arr[access_index];
    end = clock();
    total_time = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("array value: %d\n",value_arr);
    printf("Array access time time elapsed: %f\n", total_time);

    // test linked list access time
    begin = clock();
    current_node = list;
    for (int i = 0; i <= access_index; i++) {
        current_node = current_node->next;    
    }
    int value_linked_list = current_node->value;
    end = clock();
    total_time = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("linked list value: %d\n",value_linked_list);
    printf("Linked list access time elapsed: %f\n", total_time);

    // free memory (later)
}
