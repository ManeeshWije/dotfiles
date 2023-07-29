/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: MARCH 14, 2022
COURSE: CIS*3490

ASSIGNMENT 3 - MAIN FILE FOR COMMAND LOOP

*/

#include "A3Header.h"

int main(int argc, char *argv[]) {
  int input = 0;
  do {
    printf("Enter a number\n\n");
    printf("1. Brute Force Intervals Algorithm\n");
    printf("2. Presort Intervals Algorithm\n");
    printf("3. Brute Force String Search Algorithm\n");
    printf("4. Horspool String Search Algorithm\n");
    printf("5. Boyer-Moore String Search Algorithm\n");
    printf("6. Exit\n");

    scanf("%d", &input);

    if (input == 1) {
      printf("-----Starting brute force intervals-----\n");
      bruteIntervals();
      printf("-----Done brute force intervals-----\n\n");
    }
    if (input == 2) {
      printf("-----Starting presort intervals-----\n");
      presortIntervals();
      printf("-----Done presort intervals-----\n\n");
    }
    if (input == 3) {
      printf("-----Starting brute force string search-----\n");
      bruteStringSearch();
      printf("-----Done brute force string search-----\n\n");
    }
    if (input == 4) {
      printf("-----Starting Horspool string search-----\n");
      horspoolStringSearch();
      printf("-----Done Horspool string search-----\n\n");
    }
    if (input == 5) {
      printf("-----Starting Boyer-Moore string search-----\n");
      boyerMooreStringSearch();
      printf("-----Done Boyer-Moore string search-----\n\n");
    }
    if (input > 6 || input < 1) {
      printf("Error: Enter valid number\n");
      break;
    }
  } while (input != 6);
  return 0;
}
