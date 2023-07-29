/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: MARCH 14, 2022
COURSE: CIS*3490

ASSIGNMENT 3 - P11

*/

#include "A3Header.h"

int bruteIntervals() {
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
    return -1;
    fclose(fp);
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

  // algo
  // go from min to max and find highest number of occurence num. this is the
  // common point (0,5)  (-1,3)  (-2,3)  (3,6) // INTERVAL 1,2,3,4  0,1,2
  // -1,0,1,2  4,5 // POINTS IN IT 1 1 1 1  1 2 2  1 2 3 3  2 1 // OCCURRENCES
  // therefore, 1 and 2 are the common points which are in 3 intervals
  clock_t begin = clock();
  int min = arr[0];
  int max = arr[0];
  int n = sizeof(arr) / sizeof(arr[0]);
  int count = 0;
  int maxCount = 0;
  int mostCommon = 0;
  // find min and max points
  for (int i = 0; i < n; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  // brute force to find most common point and max number
  for (int i = min; i < max; i++) {
    // reset count
    count = 0;
    // j+2 because we need to skip each two as thats 1 interval
    for (int j = 0; j < n; j = j + 2) {
      if (i > arr[j] && i < arr[j + 1]) {
        // if in that range, add to count
        count++;
      }
    }
    // if that count is bigger than max, that is our max and keep checking it
    // record index of that each time as most common point
    if (count > maxCount) {
      maxCount = count;
      mostCommon = i;
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
