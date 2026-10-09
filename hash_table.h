#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdio.h>

typedef struct ht_item {
  char *key;
  char *value;
} ht_item;

typedef struct hash_table {
  ht_item **items;
  ht_item *deleted_item;
  int capacity;
  int size;
} hash_table;

ht_item *create_ht_item(const char *key, const char *value);
hash_table *ht_new();
void delete_ht_item(ht_item *item);
void delete_hash_table(hash_table *table);

void ht_insert(hash_table *ht, const char *key, const char *value);
char *ht_search(hash_table *ht, const char *key);
void ht_delete(hash_table *ht, const char *key);
void ht_print(hash_table *table);
#endif
