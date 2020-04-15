#include <stdio.h>

void print_int_array(void *array, size_t size)
{
    int *arr = (int*) array;
    printf("[");
    for (; size > 0; size--, arr++)
        printf(" %d ", *arr);
    printf("]\n");
}

int int_compare(const void *item1, const void *item2)
{
    int value1 = *((int *) item1);
    int value2 = *((int *) item2);
    return value1 == value2
        ? 0
        : (value1 < value2 ? -1 : 1);
}
