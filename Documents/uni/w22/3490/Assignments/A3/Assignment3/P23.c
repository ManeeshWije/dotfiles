/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: MARCH 14, 2022
COURSE: CIS*3490

ASSIGNMENT 3 - P23

*/

#include "A3Header.h"

// A utility function to get maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

void badCharHeuristic(char *str, int size, int badChar[256]) {
  // init all occurances to -1
  for (int i = 0; i < 256; i++) {
    badChar[i] = -1;
  }
  for (int i = 0; i < size; i++) {
    badChar[(int)str[i]] = i;
  }
}

int boyerMooreStringSearch() {
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
  int slen = strlen(str);
  int plen = strlen(pattern);
  int count = 0;
  int shiftCount = 0;
  int badChar[256];
  // generate table
  badCharHeuristic(pattern, plen, badChar);

  while (i <= (slen - plen)) {
    int j = plen - 1;
    while (j >= 0 && pattern[j] == str[i + j]) {
      j--;
    }
    if (j < 0) {
      count++;
      if (plen - badChar[(int)str[i + plen]]) {
        i += (i + plen < slen);
      } else {
        i += 1;
      }
    } else {
      shiftCount++;
      i += max(1, j - badChar[(int)str[i + j]]);
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
