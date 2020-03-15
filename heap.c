#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void push_down(void *array,
               size_t size,
               size_t index,
               int (*compare)(void *array, size_t index1, size_t index2),
               void (*swap) (void *array, size_t index1, size_t index2))
{
    print_int_array(array, size, index);
    for (;;) {
        size_t left_index = 2 * index + 1;
        size_t right_index = left_index + 1;
        int has_left_child = left_index < size;
        int has_right_child = right_index < size;
        if (!has_left_child)
            return;
        print_int_array(array, size, index);
        size_t biggest_child = left_index;
        if (has_right_child && compare(array, left_index, right_index) < 0)
            biggest_child = right_index;
        if (compare(array, biggest_child, index) <= 0)
            return;
        swap(array, index, biggest_child);
        index = biggest_child;
        print_int_array(array, size, index);
    }
}

void heapify(void *array,
             size_t size,
             size_t elem_sz,
             int (*compare)(void *, size_t index1, size_t index2),
             void (*swap) (void *, size_t index1, size_t index2))
{
  for (int i = size / 2 + 1; i >= 0; i--) {
    push_down(array, size, i, compare, swap);
  }
}


int int_bigger_than(void *array, size_t index1, size_t index2)
{
    int *arr = (int *) array;
    int value1 = *(arr + index1);
    int value2 = *(arr + index2);
    return value1 == value2
        ? 0
        : (value1 < value2 ? -1 : 1);
}

int int_less_than(void *array, size_t index1, size_t index2)
{
    return int_bigger_than(array, index2, index1);
}

void swap_int(void *array, size_t index1, size_t index2)
{
    int *arr = (int*) array;
    int tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
}

void print_int_array(void *array, size_t size, int highlight)
{
    int *arr = (int*) array;
    int numlevels = log2(size);
    for (int level = 1, i = 0;; i += level, level *= 2) {
        for (int j = 0; j < level; j++) {
            if (i + j >= size) {
                printf("\n\n");
                return;
            }
            if (i + j == highlight)
                printf("*%d* ", arr[i + j]);
            else
                printf(" %2d  ", arr[i + j]);
        }
        printf("\n");

    }
    printf("\n\n");
}

#define TEST_SIZE 10

int main(int argc, char **argv)
{
    int arr[TEST_SIZE] = {35, 5, 9, 20, 11, 3, 44, 0, 1, 23};
    heapify(arr, 10, sizeof(int), &int_bigger_than, &swap_int);
    printf("FINAL\n\n");
    print_int_array(arr, TEST_SIZE, -1);
    return 0;
}
