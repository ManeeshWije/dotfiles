/* 
NAME: MANEESH WIJEWARDHANA
ID: 1125828
COURSE: CIS*3490
DUE DATE: MARCH 28

ASSIGNMENT 4
*/ 

#include "A4Header.h"

int main(int argc, char **argv) {
  int input = 0;
  do {
    printf("Enter a number\n\n");
    printf("1. Optimal BST (DP)\n");
    printf("2. Optimal BST (Greedy)\n");
    printf("3. Gale-Shapley\n");
    printf("4. Exit\n");

    scanf("%d", &input);

    if (input == 1) {
      printf("-----Starting Optimal BST (DP)-----\n");
      P11();
      printf("-----Done Optimal BST (DP)-----\n\n");
    }
    if (input == 2) {
      printf("-----Starting Optimal BST (Greedy Technique)-----\n");
      P12();
      printf("-----Done Optimal BST (Greedy Technique)-----\n\n");
    }
    if (input == 3) {
      printf("-----Starting Gale-Shapley Algorithm-----\n");
      P2();
      printf("-----Done Gale-Shapley Algorithm-----\n\n");
    }
    if (input == 4) {
      break;
    }
    if (input > 4 || input < 1) {
      printf("Error: Enter valid number\n");
      break;
    }
  } while (input != 4);
  return 0;
}
