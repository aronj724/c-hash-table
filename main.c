#include "hash_table.h"
#include <stdio.h>

int main() {
  printf("Hello world!\n");
  printf("Second\n");
  hash_table *table;
  table = ht_new();
  char *str1 = "hello";
  char *str2 = "bye";
  create_ht_item(str1, str2, table);
  delete_hash_table(table);
  return 0;
}