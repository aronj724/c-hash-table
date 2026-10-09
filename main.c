#include "hash_table.h"
#include <stdio.h>

int main() {
  printf("Hello world!\n");
  printf("Second\n");
  hash_table *table;
  table = ht_new();
  char *array[] = {"a",      "b",    "c",    "d",     "e",     "f",   "g",
                   "barney", "is",   "my",   "enemy", "first", "he",  "died",
                   "then",   "me",   "wept", "later", "on",    "he",  "went",
                   "to",     "the",  "wild", "west",  "aay",   "bee", "cee",
                   "dee",    "eee",  "ef",   "gee",   "one",   "two", "three",
                   "four",   "five", "six",  "we"};

  for (int i = 0; i < 35; i++) {
    ht_insert(table, array[i], "he gives me the ick!");
  }
  ht_print(table);
  return 0;
}