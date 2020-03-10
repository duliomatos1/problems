#include <stdio.h>
#include <stdlib.h>

void push_down(void *array,
               size_t size,
               size_t index,
               int (*compare)(void *, void*))
{
}

void heapify(void *array, size_t size, size_t elem_sz, int (*compare)(void *, void*))
{
  for (int i = size / 2; i > 0; i--) {
    push_down(array, size, i, compare);
  }
}


int int_bigger_than(void *v1, void *v2)
{
    return *((int*) v1) < *((int*) v2);
}

int main(int argc, char **argv)
{
    int arr[10] = {35, 5, 9, 20, 11, 3, 44, 0, 1, 23};
    heapify(arr, 10, sizeof(int), int_bigger_than);
    return 0;
}
