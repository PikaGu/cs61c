/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philphix.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in 
 * the grading process.
 */
#ifndef _PHILPHIX_UNITTEST
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 1;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(0x61C, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}
#endif /* _PHILPHIX_UNITTEST */

int isValid(char c) {
  return c != ' ' && c != '\t' && c != '\n';
}

char* readWord(FILE* dict) {
  int cap = 64;
  int cur = 0;

  char c;
  char* str = (char *) malloc(sizeof(char) * cap);
  while ((c = fgetc(dict)) != EOF) {
    if (isValid(c)) {
      str[cur++] = c;
      if (cur >= cap) {
        cap *= 2;
        str = realloc(str, sizeof(char) * cap);
      }
    } else {
      if (!cur) {
        continue;
      }
      break;
    }
  }

  str[cur] = '\0';
  return str;
}

/* Task 3 */
void readDictionary(char *dictName) {
  // -- TODO --
  // fprintf(stderr, "You need to implement readDictionary\n");
  FILE* dict = fopen(dictName, "r");
  if (dict == NULL) {
    fprintf(stderr, "failed to open dict file.\n");
    exit(61);
  }

  while (1) {
    char* key = readWord(dict);
    if (key[0] == '\0') {
      break;
    }
    char* data = readWord(dict);
    insertData(dictionary, key, data);
  }

  fclose(dict);
}

char* toLowerWord(char* word, int index) {
  int cur = 0;
  int cap = 64;
  char* str = (char *) malloc(sizeof(char) * cap);
  while (word[cur] != '\0') {
    str[cur] = word[cur];
    if (cur >= index && isupper(str[cur])) {
      str[cur] = tolower(str[cur]);
    }
    cur++;
    if (cur >= cap) {
      cap *= 2;
      str = realloc(str, sizeof(char) * cap);
    }
  }
  str[cur] = '\0';
  return str;
}

char* replaceWord(char* word) {
  char* data;
  if ((data = findData(dictionary, word)) != NULL) {
    return data;
  }

  char* lower = toLowerWord(word, 1);
  if ((data = findData(dictionary, lower)) != NULL) {
    return data;
  }

  lower = toLowerWord(word, 0);
  if ((data = findData(dictionary, lower)) != NULL) {
    return data;
  }

  return word;
}

/* Task 4 */
void processInput() {
  // -- TODO --
  // fprintf(stderr, "You need to implement processInput\n");

  int cap = 64;
  int cur = 0;

  char c;
  char* str = (char *) malloc(sizeof(char) * cap);
  while ((c = fgetc(stdin)) != EOF) {
    if (isalpha(c) || isdigit(c)) {
      str[cur++] = c;
      if (cur >= cap) {
        cap *= 2;
        str = realloc(str, sizeof(char) * cap);
      }
    } else {
      if (!cur) {
        fputc(c, stdout);
        continue;
      }
      str[cur] = '\0';
      char* data = replaceWord(str);
      fputs(data, stdout);
      fputc(c, stdout);
      cur = 0;
    }
  }
  if (cur) {
    str[cur] = '\0';
    char* data = replaceWord(str);
    fputs(data, stdout);
  }
}
