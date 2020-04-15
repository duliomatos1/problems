#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1
#define GROWTH_FACTOR 2

struct array_list
{
    size_t capacity;
    size_t tail_position;
    void *buffer;
    size_t element_size;
};

void init_array_list(struct array_list *list, size_t element_size)
{
    list->capacity = INITIAL_SIZE;
    list->tail_position = 0;
    list->element_size = element_size;
    list->buffer = malloc(list->capacity * element_size);
}

void print_int_array_list(struct array_list *list)
{
    if (list->tail_position == 0) {
        printf("NIL");
    } else {
        for (size_t i = 0; i < list->tail_position; i++) {
            int elem = ((int*)list->buffer)[i];
            printf("%d ", elem);
        }
    }
    printf("\n");
}

void grow_buffer(struct array_list *list)
{
    size_t new_capacity = list->capacity * GROWTH_FACTOR;
    list->buffer = realloc(list->buffer, new_capacity);
    list->capacity = new_capacity;
    printf("resize to %ld\n", new_capacity);
}

int array_list_insert(struct array_list *list, size_t position, void *element)
{
    if (position > list->capacity)
        return 0;
    if (list->tail_position >= list->capacity)
        grow_buffer(list);

    void *current_element = malloc(list->element_size);
    void *next_element = malloc(list->element_size);
    memcpy(current_element, element, list->element_size);

    for (size_t i = position; i <= list->tail_position; i++) {
        void *buf_addr = ((char*) list->buffer) + list->element_size * i;
        memcpy(next_element, buf_addr, list->element_size);
        memcpy(buf_addr, current_element, list->element_size);
        memcpy(current_element, next_element, list->element_size);
    }
    free(next_element);
    free(current_element);
    list->tail_position++;

    return 1;
}

int array_list_remove(struct array_list *list, size_t position)
{
    if (position >= list->tail_position)
        return 0;
    for (size_t i = position; i < list->tail_position; i++) {
        memcpy(list->buffer + i * list->element_size,
               list->buffer + (i + 1) * list->element_size,
               list->element_size);
    }
    list->tail_position--;
    return 1;
}

int array_list_add(struct array_list *list, void *element)
{
    return array_list_insert(list, list->tail_position, element);
}

void* array_list_at(struct array_list *list, size_t position)
{
    if (position >= list->tail_position)
            return NULL;
    return ((char*) list->buffer) + position * list->element_size;
}

#define GEN_ARRAY_LIST_AT(name,type) \
type array_list_ ## name ## _at(struct array_list *list, size_t pos) \
{ \
    return *((type*) array_list_at(list, pos)); \
}

GEN_ARRAY_LIST_AT(int,int)
GEN_ARRAY_LIST_AT(double,double)
GEN_ARRAY_LIST_AT(str,char*)

int main(int argc, char **argv)
{
    int elements[] = {32, 98, 54, 21, 43};
    struct array_list list;

    init_array_list(&list, sizeof(int));
    for (int i = 0; i < 5; i++) {
        array_list_add(&list, elements + i);
    }
    print_int_array_list(&list);
    array_list_remove(&list, 2);
    print_int_array_list(&list);

    int elem = *((int*) array_list_at(&list, 3));
    printf("Element 3: %d\n", elem);

    elem = array_list_int_at(&list, 1);
    printf("Element 1: %d\n", elem);

    char* str_elements[] = {"Hello", "World", "Brazil"};
    struct array_list str_list;
    init_array_list(&str_list, sizeof(char*));
    for (int i = 0; i < 3; i++) {
        printf("%s\n", str_elements[i]);
        array_list_add(&str_list, &str_elements[i]);
    }
    printf("Element 1: %s\n", array_list_str_at(&str_list, 1));
}
