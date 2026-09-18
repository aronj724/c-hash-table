/*
1. Our key-value pairs (items) will each be stored in a struct
2. Our hash table stores an array of pointers to items, and some details about
its size and how full it is:
*/
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdio.h>

typedef struct ht_item {
  char *key;
  char *value;
} ht_item;

typedef struct hash_table {
  ht_item **items;
  int capacity;
  int size;
} hash_table;

void create_ht_item(char *key, char *value, hash_table *table);
hash_table *ht_new();
void delete_ht_item(ht_item *item);
void delete_hash_table(hash_table *table);
#endif