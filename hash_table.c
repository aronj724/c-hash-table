/*
1.We need to define initialisation functions for ht_items. This function
allocates a chunk of memory the size of an ht_item, and saves a copy of the
strings k and v in the new chunk of memory. The function is marked as static
because it will only ever be called by code internal to the hash table.
2. ht_new initialises a new hash table. size defines how many items we can
store. This is fixed at 53 for now. We'll expand this in the section on
resizing. We initialise the array of items with calloc, which fills the
allocated memory with NULL bytes. A NULL entry in the array indicates that the
bucket is empty.
3. We also need functions for deleting ht_items and ht_hash_tables, which free
the memory we've allocated, so we don't cause memory leaks.
4. We have written code which defines a hash table, and lets us create and
destroy one. Although it doesn't do much at this point, we can still try it out.
*/

#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  table->items[table->size] = item;
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
  for (int i = 0; i < table->size; i++) {
    delete_ht_item(table->items[i]);
  }
  free(table->items);
  free(table);
}
