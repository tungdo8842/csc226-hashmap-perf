#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LENGTH 100
#define INSERTION_AMOUNT 75
#define LOOP_AMOUNT 100*1000

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

int hash(int value) {
    return value % ARRAY_LENGTH;
}

void clear_values(int dict_arr_probing[], ListNode *lists[ARRAY_LENGTH]);
void insert_arr(int dict_arr_probing[], int value);
void insert_linked_list(ListNode *lists[ARRAY_LENGTH], int value);

int main() {
    clock_t begin = clock();
    // random data generated with python
    int data_arr_rand[] = {2202, 9326, 1034, 4180, 1932, 8118, 7365, 7738, 6220, 3440, 1538, 7994, 465, 6387, 7091, 9953, 35, 7298, 4364, 3749, 
        9686, 1675, 5201, 502, 366, 417, 8871, 151, 6246, 3549, 6916, 476, 8645, 3633, 7175, 8124, 9059, 3819, 5664, 3783, 
        3585, 7531, 4748, 353, 6819, 9117, 1639, 3046, 4857, 1981, 5451, 8206, 8319, 3111, 4971, 4656, 9627, 8182, 8279, 6445, 
        9651, 566, 7869, 3978, 6624, 6789, 2835, 6015, 8992, 6140, 1417, 7192, 8331, 1769, 2683, 8536, 6444, 6071, 8024, 485, 
        7690, 713, 5055, 9719, 9473, 6449, 2792, 2763, 8229, 3719, 202, 3269, 8842, 8984, 3804, 6627, 8418, 5634, 9467, 5789};
    int data_arr_sequential[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
        40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
        60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};
    int data_arr_worst_case[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900,
        2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900,
        4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 5000, 5100, 5200, 5300, 5400, 5500, 5600, 5700, 5800, 5900,
        6000, 6100, 6200, 6300, 6400, 6500, 6600, 6700, 6800, 6900, 7000, 7100, 7200, 7300, 7400, 7500, 7600, 7700, 7800, 7900, 
        8000, 8100, 8200, 8300, 8400, 8500, 8600, 8700, 8800, 8900, 9000, 9100, 9200, 9300, 9400, 9500, 9600, 9700, 9800, 9900};

    // initialization
    int dict_arr_probing[ARRAY_LENGTH];
    ListNode **lists = (ListNode**)malloc(sizeof(ListNode*) * ARRAY_LENGTH);

    printf("this should prints out\n");
    // initialize values for all arrays and lists
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        dict_arr_probing[i] = -1; // -1 for empty (use positive value only)
        ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
        lists[i] = new_node;
        lists[i]->value = -1;
        lists[i]->next = NULL;
    }

    clock_t end = clock();
    double total_time = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("initialization time: %f\n", total_time);

    printf("Testing hashmap insertion with array size %d, load factor 0.75\n", ARRAY_LENGTH);
    printf("Using randomly genrated values");

    total_time = 0;
    for (int loop_count = 0; loop_count<LOOP_AMOUNT; loop_count++) {
        begin = clock();
        for (int i = 0; i < ARRAY_LENGTH; i++) {
            insert_arr(dict_arr_probing, data_arr_rand[i]);
        }
        end = clock();
        total_time += (end - begin);
        clear_values(dict_arr_probing, lists);
    }
    total_time = total_time / CLOCKS_PER_SEC;
    printf("Linear Probing insertion time: %f\n", total_time);

    total_time = 0;
    for (int loop_count = 0; loop_count<LOOP_AMOUNT; loop_count++) {
        begin = clock();
        for (int i = 0; i < ARRAY_LENGTH; i++) {
            insert_linked_list(lists, data_arr_worst_case[i]);
        }
        end = clock();
        total_time += (end - begin);
        clear_values(dict_arr_probing, lists);
    }
    total_time = total_time / CLOCKS_PER_SEC;
    printf("Chaining insertion time: %f\n", total_time);
    

    // no freeing memory this time (freed on program exit)
}

void clear_values(int dict_arr_probing[], ListNode *lists[ARRAY_LENGTH]){
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        dict_arr_probing[i] = -1; // -1 for empty (use positive value only)
        lists[i]->value = -1;
        lists[i]->next = NULL;
    }
}

void insert_arr(int dict_arr_probing[], int value) {
    int index = hash(value);
    for (int i = index; i < ARRAY_LENGTH; i++) {
        if (dict_arr_probing[i] != -1) {
            dict_arr_probing[i] = value;
            return;
        }
    }    
    return;
}

void insert_linked_list(ListNode *lists[ARRAY_LENGTH], int value){
    int index = hash(value);
    ListNode *current = lists[index];
    while (current->value != -1) {
        if (current->next == NULL){
            ListNode *new = malloc(sizeof(ListNode));
            new->next = NULL;
            new->value = value;
            return;
        }
        current = current->next;
    }
    current->value = value;
}
    
