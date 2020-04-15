#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

typedef void (*SORTFUN)(void *,
                        size_t,
                        size_t,
                        int (*compare)(const void *, const void *));

void quicksort(void *array,
               size_t nitems,
               size_t size,
               int (*compare)(const void *value1, const void *value2))
{
    if (nitems < 2)
        return;
    // pivot wil be the last element
    void *pivot = ((char *) array) + size * (nitems - 1);

    char *copy_buf = malloc(size);
    char *insert_pos = (char *) array;
    size_t pivot_pos = 0;
    for (char *candidate = insert_pos; candidate != pivot; candidate += size) {
        if (compare(candidate, pivot) < 0) {
            if (candidate != insert_pos) {
                memcpy(copy_buf, insert_pos, size);
                memcpy(insert_pos, candidate, size);
                memcpy(candidate, copy_buf, size);
            }
            insert_pos += size;
            ++pivot_pos;
        }
    }
    memcpy(copy_buf, insert_pos, size);
    memcpy(insert_pos, pivot, size);
    memcpy(pivot, copy_buf, size);
    free(copy_buf);

    quicksort(array, pivot_pos, size, compare);
    quicksort(insert_pos + size, nitems - pivot_pos - 1, size, compare);
}

void test_sort(SORTFUN sort)
{
    const int nitems = 10;
    int array[] = {3, 22, 43, 1, 9, 15, 0, 18, 99, 32};

    print_int_array(array, nitems);
    sort(array, nitems, sizeof(int), &int_compare);
    print_int_array(array, nitems);
}

void test_quicksort()
{
    test_sort(&quicksort);
}

void mergesort_merge(char *array1,
                     char *array2,
                     size_t middle,
                     size_t nitems,
                     size_t size,
                     int (*compare)(const void *value1, const void *value2))
{
    size_t left = 0;
    size_t right = middle;
    for (size_t i = 0; i < nitems; i++) { 
        if (left <= middle && (right >= size
                               || compare(array1 + left * size,
                                          array1 + right * size) <= 0)) {
            *(array2 + i * size) = *(array1 + left * size);
            left += size;
        } else {
            *(array2 + i * size) = *(array1 + right * size);
            right += size;
        }
    }
}

void mergesort_split(char *array1,
                     char *array2,
                     size_t nitems,
                     size_t size,
                     int (*compare)(const void *value1, const void *value2))
{
    if (nitems <= 1)
        return;
    printf("nitems: %d\n", nitems);
    size_t middle = nitems / 2;
    mergesort_split(array2,
                    array1,
                    middle,
                    size,
                    compare);
    mergesort_split(array1 + middle * size,
                    array2 + middle * size,
                    nitems - middle,
                    size,
                    compare);
    mergesort_merge(array1, array2, middle, nitems, size, compare);
}

void mergesort(void *array,
               size_t nitems,
               size_t size,
               int (*compare)(const void *value1, const void *value2))
{
    const size_t array_size = nitems * size;
    void *copy = malloc(array_size);
    memcpy(copy, array, array_size);
    mergesort_split((char *) copy, (char *) array, nitems, size, compare); 
}

void test_mergesort()
{
    test_sort(&mergesort);
}


int main(int argc, char **argv)
{
    test_mergesort();
}
