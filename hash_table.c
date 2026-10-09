#include "hash_table.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELETED &ht_item("deleted", "deleted");

// returns an index given a key string the number of buckets in the hash table
// and a specific prime number
int hash(const char *string, int num_buckets, int prime_number) {
  double hash = 0;
  int str_len = strlen(string);
  for (int i = 0; i < str_len; i++) {
    hash +=
        pow((double)prime_number, (double)(str_len - i - 1)) * (int)(string[i]);
  }
  return (int)fmod(hash, (double)num_buckets);
}

// given a key string and value string this function creates an ht_item
ht_item *create_ht_item(const char *key, const char *value) {
  ht_item *item = malloc(sizeof(ht_item));
  char *key_string = malloc(strlen(key) + 1);
  char *value_string = malloc(strlen(value) + 1);
  strncpy(key_string, key, strlen(key));
  strncpy(value_string, value, strlen(value));
  key_string[strlen(key_string)] = '\0';
  value_string[strlen(value_string)] = '\0';
  printf("completed\n");
  item->key = key_string;
  item->value = value_string;
  return item;
};

// create a new hash table with original capacity of 53 items and reture address
// of the hash table
hash_table *ht_new() {
  hash_table *ht = malloc(sizeof(hash_table));
  ht->capacity = 53;
  ht->size = 0;
  ht->items = calloc(ht->capacity, sizeof(ht_item *));
  ht->deleted_item = create_ht_item("deleted", "deleted");
  return ht;
};

// deletes a ht_item given a
void delete_ht_item(ht_item *item) {
  free(item->key);
  free(item->value);
  free(item);
}

// deletes table given a hash table pointer
void delete_hash_table(hash_table *table) {
  for (int i = 0; i < table->capacity; i++) {
    if (table->items[i] != NULL) {
      delete_ht_item(table->items[i]);
    }
  }
  free(table->items);
  free(table);
}

// creates an ht_item using key and value and adds it to ht
void ht_insert(hash_table *table, const char *key, const char *value) {
  ht_item *item = create_ht_item(key, value);
  int index = -1;
  int iteration = 0;
  int prime_num_1 = 151;
  int prime_num_2 = 307;
  // continue to search if either the value at the index is NULL or a point to
  // deleted item
  do {
    index = (hash(item->key, table->capacity, prime_num_1) +
             iteration * (hash(item->key, table->capacity, prime_num_2) + 1)) %
            table->capacity;
    if (table->items[index] != NULL &&
        table->items[index] != table->deleted_item) {
      if ((int)strcmp(table->items[index]->key, key) == 0) {
        ht_delete(table, key);
        break;
      }
    }

    printf("This is attempt %d: Index is %d\n", iteration, index);
    iteration++;
  } while (table->items[index] != NULL &&
           table->items[index] != table->deleted_item);
  printf("This is the index for %s: %d\n", key, index);
  table->items[index] = item;
  table->size++;
}

// return the value of the ht_item given the key(string) and table(table*)
char *ht_search(hash_table *table, const char *key) {
  int index = -1;
  int iteration = 0;
  int prime_num_1 = 151;
  int prime_num_2 = 307;
  do {
    index = (hash(key, table->capacity, prime_num_1) +
             iteration * (hash(key, table->capacity, prime_num_2) + 1)) %
            table->capacity;
    iteration++;
    if ((int)strcmp(key, table->items[index]->key) == 0) {
      return table->items[index]->value;
    }
  } while (table->items[index] != NULL);
  return NULL;
}

// deletes the ht_item corresponding to key(string)
void ht_delete(hash_table *table, const char *key) {
  int index = -1;
  int iteration = 0;
  int prime_num_1 = 151;
  int prime_num_2 = 307;
  do {
    index = (hash(key, table->capacity, prime_num_1) +
             iteration * (hash(key, table->capacity, prime_num_2) + 1)) %
            table->capacity;
    iteration++;
    if ((int)strcmp(key, table->items[index]->key) == 0) {
      table->items[index] = table->deleted_item;
      break;
    }
  } while (table->items[index] != NULL);
  table->size--;
}

// prints a hash table
void ht_print(hash_table *table) {
  printf("{\n");
  for (int i = 0; i < table->capacity; i++) {
    if (table->items[i] != NULL && table->items[i] != table->deleted_item) {
      printf("    \"%s\": \"%s\"\n", table->items[i]->key,
             table->items[i]->value);
    }
  }
  printf("}\n");
}