/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: FEB 14, 2022
COURSE: CIS*3490

ASSIGNMENT 2 - MAIN FILE FOR COMMAND LOOP

*/

#include "A2Header.h"

int main(int argc, char *argv[]) {
  int input = 0;
  do {
    printf("Enter a number\n\n");
    printf("1. Brute Force Inversions\n");
    printf("2. Recursive Divide-and-Conquer Inversions\n");
    printf("3. Brute Force Convex Hull\n");
    printf("4. Recursive Divide-and-Conquer Convex Hull\n");
    printf("5. Exit\n");

    scanf("%d", &input);

    if (input == 1) {
      printf("-----Starting brute force inversions-----\n");
      printf("Number of inversions: %d\n", bruteForceInversions());
      printf("-----Done brute force inversions-----\n\n");
    }
    if (input == 2) {
      printf("-----Starting recursive divide-and-conquer inversions-----\n");
      printf("Number of inversions: %d\n", mergeSortInversions());
      printf("-----Done recursive divide-and-conquer inversions-----\n\n");
    }
    if (input == 3) {
      printf("-----Starting brute force convex hull-----\n");
      bruteForceConvexHull();
      printf("-----Done brute force convex hull-----\n\n");
    }
    if (input == 4) {
      printf("-----Starting recursive divide-and-conquer convex hull-----\n");
      quickConvexHull();
      printf("-----Done recursive divide-and-conquer convex hull-----\n\n");
    }
    if (input > 5 || input < 1) {
      printf("Error: Enter valid number\n");
      break;
    }
  } while (input != 5);
  return 0;
}
