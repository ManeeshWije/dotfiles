/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: MARCH 14, 2022
COURSE: CIS*3490

ASSIGNMENT 3 - P21

*/

#include "A3Header.h"

// try to match the first character of the pattern with the first character of
// the text if we succeed, try to match the second character, and so on if we
// hit a failure point, slide the pattern over one character and try again and
// record this count When we find a match increment count

int bruteStringSearch() {
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
  int slen = strlen(str);
  int plen = strlen(pattern);
  int count = 0;
  int shiftCount = 0;

  // printf("string len: %d, pattern len: %d\n", slen, plen);

  clock_t begin = clock();
  for (int i = 0; i < slen - plen; i++) {
    // reset j
    int j = 0;
    while (j < plen && pattern[j] == str[i + j]) {
      // if match found, increment j
      j++;
    }
    // only if j is equal to the length of pattern do we increment our count
    if (j == plen) {
      count++;
    } else {
      // if not, it will shift to next so record that shift count as well
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
