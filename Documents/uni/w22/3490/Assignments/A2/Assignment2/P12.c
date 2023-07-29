/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: FEB 14, 2022
COURSE: CIS*3490

ASSIGNMENT 2 - COUNTING INVERSIONS

*/

#include "A2Header.h"

int merge(int arr[], int temp[], int left, int mid, int right) {
  int inversions = 0;
  int i = left; // i is index for left subarray
  int j = mid; // j is index for right subarray
  int k = left; // k is index for resultant merged subarray
  while (i <= mid - 1 && j <= right) {
    if (arr[i] <= arr[j]) {
        temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
      inversions = inversions + (mid - i);
    }
  }
  // Copy the remaining elements of left subarray (if there are any) to temp
  while (i <= mid - 1) {
    temp[k] = arr[i];
    k++;
    i++;
  }
  // Copy the remaining elements of right subarray (if there are any) to temp
  while (j <= right) {
    temp[k] = arr[j];
    k++;
    j++;
  }
  // Copy back the merged elements to original array
  for (i = left; i <= right; i++) {
    arr[i] = temp[i];
  }
  // inversion count
  return inversions;
}

int mergeSort(int arr[], int temp[], int left, int right) {
  int mid;
  int count1 = 0;
  int count2 = 0;
  int count3 = 0;
  int totalCount = 0;
  if (right > left) {
    // Middle point to divide the array into two halves
    mid = (right + left) / 2;
    // Inversion count of left and right parts
    count1 += mergeSort(arr, temp, left, mid);
    count2 += mergeSort(arr, temp, mid + 1, right);
    // Inversion Counts during merging the two sorted parts
    count3 += merge(arr, temp, left, mid + 1, right);
  }
  // total inversion count;
  totalCount = count1 + count2 + count3;
  return totalCount; 
}


int mergeSortInversions() {
  char buff[10000];
  int arr[50000];
  char *token;

  FILE* fp = fopen("data_A2_Q1.txt", "r");

  if (fp == NULL) {
    printf("Could not open file\n");
    return -1;
  }

  int i = 0;
  // parse each line in file
  while (fgets(buff, sizeof(buff), fp)) {
    // remove newline
    strtok(buff, "\n");
    // split on space
    token = strtok(buff, " ");
    while (token != NULL) {
      // add each number to int array
      arr[i] = atoi(token);
      // printf("%d %d\n", i, arr[i]); 
      token = strtok(NULL, " ");
      i++;
    }
  }   
  // size
  int n = sizeof(arr) / sizeof(arr[0]);
  int temp[n];
  clock_t begin = clock();
  int inv = mergeSort(arr, temp, 0, n - 1);
  clock_t end = clock();
  double timeSeconds = (double)(end - begin) / CLOCKS_PER_SEC;
  int timeMille = 1000 * timeSeconds;
  printf("Execution time: %dms\n", timeMille);
  return inv;
}
