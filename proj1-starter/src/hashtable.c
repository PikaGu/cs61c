#include "hashtable.h"

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  if (NULL == newTable) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  newTable->size = size;
  newTable->buckets = malloc(sizeof(struct HashBucketEntry *) * size);
  if (NULL == newTable->buckets) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  for (i = 0; i < size; i++) {
    newTable->buckets[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/* Task 1.2 */
void insertData(HashTable *table, void *key, void *data) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket location with table->hashFunction.
  // 2. Allocate a new hash bucket entry struct.
  // 3. Append to the linked list or create it if it does not yet exist. 
  unsigned int loc = table->hashFunction(key) % table->size;
  HashBucketEntry* entry = (HashBucketEntry*) malloc(sizeof(HashBucketEntry));
  entry->key = key;
  entry->data = data;
  if (table->buckets[loc] != NULL) {
    entry->next = table->buckets[loc];
  }
  table->buckets[loc] = entry;
}

/* Task 1.3 */
void *findData(HashTable *table, void *key) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  // 2. Walk the linked list and check for equality with table->equalFunction.
  unsigned int loc = table->hashFunction(key) % table->size;
  HashBucketEntry* cur = table->buckets[loc];
  while (cur) {
    if (table->equalFunction(key, cur->key)) {
      return cur->data;
    }
    cur = cur->next;
  }
  return NULL;
}

/* Task 2.1 */
unsigned int stringHash(void *s) {
  // -- TODO --
  // fprintf(stderr, "need to implement stringHash\n");
  /* To suppress compiler warning until you implement this function, */
  unsigned int result = 0;
  char* str = (char*) s;
  while (*str != '\0') {
    result = result * 255 + *str;
    str++;
  }
  return result;
}

/* Task 2.2 */
int stringEquals(void *s1, void *s2) {
  // -- TODO --
  // fprintf(stderr, "You need to implement stringEquals");
  /* To suppress compiler warning until you implement this function */
  char* str1 = (char*) s1;
  char* str2 = (char*) s2;
  while (*str1 != '\0' || *str2 != '\0') {
    if (*str1 != *str2) {
      return 0;
    }
    str1++;
    str2++;
  }
  return 1;
}