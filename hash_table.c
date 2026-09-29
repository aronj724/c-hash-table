#include "hash_table.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash_a(char *string, int num_buckets) {
  double hash = 0;
  int prime_num = 151;
  int str_len = strlen(string);
  for (int i = 0; i < str_len; i++) {
    hash +=
        pow((double)prime_num, (double)(str_len - i - 1)) * (int)(string[i]);
  }
  return (int)fmod(hash, (double)num_buckets);
}

int hash_b(char *string, int num_buckets) {
  double hash = 0;
  int prime_num = 307;
  int str_len = strlen(string);
  for (int i = 0; i < str_len; i++) {
    hash +=
        pow((double)prime_num, (double)(str_len - i - 1)) * (int)(string[i]);
  }
  return (int)fmod(hash, (double)num_buckets);
}
/*
Given a key string and value string this function creates an ht_item
*/
void create_ht_item(char *key, char *value, hash_table *table) {
  ht_item *item = malloc(sizeof(ht_item));
  char *key_string = malloc(sizeof(key));
  char *value_string = malloc(sizeof(value));
  strncpy(key_string, key, sizeof(key_string) - 1);
  strncpy(value_string, value, sizeof(value_string) - 1);
  key_string[sizeof(key_string) - 1] = '\0';
  value_string[sizeof(value_string) - 1] = '\0';
  printf("completed\n");
  item->key = key_string;
  item->value = value_string;
  int index = -1;
  int iteration = 0;
  printf("New key: %s\n", item->key);
  do {
    index = (hash_a(item->key, table->capacity) +
             iteration * (hash_b(item->key, table->capacity) + 1)) %
            table->capacity;
    printf("This is attempt %d: Index is %d\n", iteration, index);
    iteration++;
  } while (table->items[index] != NULL);
  printf("This is the index: %d\n", index);
  table->items[index] = item;
  table->size++;
};

/*
Create a new hash table with original capacity of 53 items and reture address of
the hash table
*/
hash_table *ht_new() {
  hash_table *ht = malloc(sizeof(hash_table));
  ht->capacity = 53;
  ht->size = 0;
  ht->items = calloc(ht->capacity, sizeof(ht_item *));
  return ht;
};

void delete_ht_item(ht_item *item) {
  free(item->key);
  free(item->value);
  free(item);
}

void delete_hash_table(hash_table *table) {
  for (int i = 0; i < table->capacity; i++) {
    if (table->items[i] != NULL) {
      delete_ht_item(table->items[i]);
    }
  }
  free(table->items);
  free(table);
  char *string = "cat";
  int num = 53;
  printf("This is the index: %d\n", hash_a(string, num));
}
