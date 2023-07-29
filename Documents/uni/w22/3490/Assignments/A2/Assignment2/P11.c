/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: FEB 14, 2022
COURSE: CIS*3490

ASSIGNMENT 2 - COUNTING INVERSIONS

*/

#include "A2Header.h"

int bruteForceInversions() {
  char buff[10000];
  int arr[50000];
  char *token;

  FILE* fp = fopen("data_A2_Q1.txt", "r");

  if (fp == NULL) {
    printf("Could not open file\n");
    return -1;
  }

  int i = 0;
  // parsing each line
  while (fgets(buff, sizeof(buff), fp)) {
    // remove newline
    strtok(buff, "\n");
    // splitting on space
    token = strtok(buff, " ");
    while (token != NULL) {
      // adding each number to int array
      arr[i] = atoi(token);
      printf("%d %d\n", i, arr[i]); 
      token = strtok(NULL, " ");
      i++;
    }
  }   

  int inversions = 0;
  // size
  int n = sizeof(arr) / sizeof(arr[0]);
  clock_t begin = clock();
  // go through array once
  for (int j = 0; j < n; j++) {
    // go through array another time skipping first element
    for (int k = j + 1; k < n; k++) {
      // if left bigger than right, thats an inversion so increment
      if (arr[j] > arr[k]) {
        inversions++;
      }
    }
  }
  clock_t end = clock();
  double timeSeconds = (double)(end - begin) / CLOCKS_PER_SEC;
  int timeMille = 1000 * timeSeconds;
  printf("Execution time: %dms\n", timeMille);
  return inversions;
}
