#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_BUCKETS 128

typedef struct element {
  void* key;
  void* value;
  struct element* next;
} element;

typedef struct {
  element buffer[NUM_BUCKETS];
  size_t key_size;
  size_t element_size;
  size_t (*make_hash)(void *);
  // TODO include pointer to key comparison function
} hashtable;

typedef struct {
  hashtable* table;
  size_t cur_bucket;
  element* cur_pos;
} hashtable_iter;

typedef struct {
  void *key;
  void *value;
} hashtable_key_value;

void make_hashtable(
    hashtable *table,
    size_t key_size,
    size_t element_size,
    size_t (*make_hash)(void *)) {
  table->key_size = key_size;
  table->element_size = element_size;
  table->make_hash = make_hash;
  for (int i=0; i < NUM_BUCKETS; i++) {
    table->buffer[i].key = NULL;
    table->buffer[i].value = NULL;
    table->buffer[i].next = NULL;
  }
}

size_t make_hash_int(void* item) {
  return ((size_t) *((int*) item) * 13 + 17) % NUM_BUCKETS;
}

int equal_keys(hashtable* table, void* key1, void* key2) {
  char *k1 = (char*) key1;
  char *k2 = (char*) key2;
  for (size_t i=0; i < table->key_size; i++) {
    if (*(k1 + i) != *(k2 + i)) {
      return 0;
    }
  }
  return 1;
}

void put(hashtable* table, void* key, void* item) {
  size_t hash = table->make_hash(key);
  element* position = &table->buffer[hash];
  while (1) {
    if (position->key == NULL || equal_keys(table, key, position->key)) {
      position->key = key;
      position->value = item;
      return;
    }
    if (position->next != NULL) {
      position = position->next;
    } else {
      break;
    }
  }

  element* new_element = malloc(sizeof(element));
  position->next = new_element;
  new_element->key = key;
  new_element->value = item;
  new_element->next = NULL;
}

hashtable_iter make_iter(hashtable* table) {
  hashtable_iter iter;
  iter.table = table;
  iter.cur_bucket = 0;
  iter.cur_pos = &table->buffer[0];
  return iter;
}

void* next_key(hashtable_iter* iter) {
  while (iter->cur_pos == NULL || iter->cur_pos->key == NULL) {
    iter->cur_bucket++;
    if (iter->cur_bucket >= NUM_BUCKETS) return NULL;
    iter->cur_pos = &iter->table->buffer[iter->cur_bucket];
  }
  void *key= iter->cur_pos->key;
  iter->cur_pos = iter->cur_pos->next;
  return key;
}

hashtable_key_value next_key_value(hashtable_iter* iter) {
  hashtable_key_value kv;
  kv.key = NULL;
  kv.value = NULL;
  while (iter->cur_pos == NULL || iter->cur_pos->key == NULL) {
    iter->cur_bucket++;
    if (iter->cur_bucket >= NUM_BUCKETS) return kv;
    iter->cur_pos = &iter->table->buffer[iter->cur_bucket];
  }
  kv.key = iter->cur_pos->key;
  kv.value = iter->cur_pos->value;
  iter->cur_pos = iter->cur_pos->next;
  return kv;
}

void* get(hashtable* table, void *key) {
  size_t hash = table->make_hash(key);
  element* position = &table->buffer[hash];
  do {
    if (equal_keys(table, key, position->key)) {
      return position->value;
    }
    position = position->next;
  } while (position != NULL);
  return NULL;
}

void test_print_all_from_key_iter(hashtable *table) {
  hashtable_iter iter = make_iter(table);
  printf("print all key, value pairs\n");
  void *key;
  while ((key = next_key(&iter)) != NULL) {
    int *k = (int *) key;
    int *v= (int*) get(table, key);
    printf("%d: %d\n", *k, *v);
  }
}

void test_print_all_from_key_value_iter(hashtable *table) {
  hashtable_iter iter = make_iter(table);
  printf("print all key, value pairs\n");
  hashtable_key_value kv;

  while ((kv = next_key_value(&iter)) != NULL) {
    int *k = (int *) key;
    int *v= (int*) get(table, key);
    printf("%d: %d\n", *k, *v);
  }
}

void test_print_all(hashtable *table) {
  for (int k=0; k < 1000; k++) {
    int *v= (int*) get(table, &k);
    printf("%d: %d\n", k, *v);
  }
}

int main(int argc, char** argv) {
  int keys[1000];
  int values[1000];
  hashtable table;
  make_hashtable(&table, sizeof(int), sizeof(int), &make_hash_int);
  
  for (int i=0; i < 1000; i++) {
    keys[i] = i;
    values[i] = i*i;
    put(&table, &keys[i], &values[i]);
  }
  test_print_all(&table);
}
