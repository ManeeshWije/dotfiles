/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: MARCH 14, 2022
COURSE: CIS*3490

ASSIGNMENT 3 - P12

*/

#include "A3Header.h"

// struct to organize x and y values
typedef struct Data {
  int first;
  char second;
} Data;

// compare function to use in qsort call
int cmpfunc(const void * a, const void * b) {
  return (*(int*)a - *(int*)b);
}

// A utility function to get maximum of two integers
int maxFunc(int a, int b) { return (a > b) ? a : b; }

int presortIntervals() {
  // declare vars
  char filename[100] = "";
  char buff[256];
  int arr[60000];
  char *token;
  int i = 0;
  printf("Enter filename: ");
  scanf("%s", filename);
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("Could not open file\n");
    fclose(fp);
    return -1;
  }

  // file reading and parsing stuff
  while (fgets(buff, sizeof(buff), fp)) {
    // remove newline
    strtok(buff, "\n");
    // splitting on space
    token = strtok(buff, " ");
    while (token != NULL) {
      // adding each number to int array
      arr[i] = atoi(token);
      // printf("%d %d\n", i, arr[i]);
      token = strtok(NULL, " ");
      i++;
    }
  }
  fclose(fp);

  clock_t begin = clock();
  int n = sizeof(arr) / sizeof(arr[0]);
  int count = 0;
  int maxCount = 0;
  int mostCommon = 0;

  // record x and y values in struct
  Data d[60000];
  for (int i = 0; i < n; i += 2) {
    d[i].first = arr[i] + 1;
    d[i].second = 'x';
    d[i + 1].first = arr[i + 1];
    d[i + 1].second = 'y';
  }

  // sort the struct
  qsort(d, n, sizeof(Data), &cmpfunc);

  // for (int i = 0; i < n; i++) {
  //   printf("s:%d e:%c\n", d[i].first, d[i].second);
  // }

  // now increment if we see an x but decrement for the next y and at the end
  // we will have our count
  for (int i = 0; i < n; i++) {
    if (d[i].second == 'x') {
      count += 1;
    }
    if (d[i].second == 'y') {
      count -= 1;
    }
    if (count > maxCount) {
      maxCount = count;
      mostCommon = d[i].first;
    }
  }

  clock_t end = clock();
  double timeSeconds = (double)(end - begin) / CLOCKS_PER_SEC;
  int timeMille = 1000 * timeSeconds;
  printf("The maximum number of intervals: %d\n", maxCount);
  printf("The intervals include point: %d\n", mostCommon);
  printf("Time for finding the maximum number: %dms\n", timeMille);

  return 0;
}
