/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: MARCH 14, 2022
COURSE: CIS*3490

ASSIGNMENT 3 - P22

*/

#include "A3Header.h"

void shiftTable(char *pattern, int *table) {
  int plen = strlen(pattern);
  for (int i = 0; i < 500; i++) {
    table[i] = plen;
  }
  for (int i = 0; i < plen - 1; i++) {
    table[(int)pattern[i]] = plen - 1 - i;
  }
}

int horspoolStringSearch() {
  char *filename = "data_A3_Q2.txt";
  char *str = malloc(sizeof(char) * 3332345);
  char buff[256];
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("Could not open file\n");
    fclose(fp);
    return -1;
  }

  // read file and continuosly concatenate into malloced string
  while (fgets(buff, 256, fp)) {
    strcat(str, buff);
  }
  fclose(fp);

  // printf("%s\n", str);

  char *pattern = malloc(sizeof(char) * 10000);
  printf("Enter a pattern: ");
  scanf("%s", pattern);

  clock_t begin = clock();
  int i = 0;
  int j = 0;
  int slen = strlen(str);
  int plen = strlen(pattern);
  int count = 0;
  int shiftCount = 0;
  int table[500];
  // generate table
  shiftTable(pattern, table);
  i = plen - 1;
  // loop until end of str
  while (i < slen) {
    j = 0;
    while ((j < plen) && (pattern[plen - 1 - j] == str[i - j])) {
      j++;
    }
    if (j == plen) {
      // match found
      count++;
      i += plen;
    } else {
      // if not, add to shift table
      i += table[(int)str[i]];
      // increment shiftcount
      shiftCount++;
    }
  }
  clock_t end = clock();
  double timeSeconds = (double)(end - begin) / CLOCKS_PER_SEC;
  int timeMille = 1000 * timeSeconds;
  printf("Count: %d\n", count);
  printf("Shifts: %d\n", shiftCount);
  printf("Execution time: %dms\n", timeMille);

  return 0;
}
