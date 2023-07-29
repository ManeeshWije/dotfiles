/* 
NAME: MANEESH WIJEWARDHANA
ID: 1125828
COURSE: CIS*3490
DUE DATE: MARCH 28

ASSIGNMENT 4
*/ 
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_WORD_LENGTH 60503

// to store the words and their frequencies
// and their probabilities
typedef struct Node {
  char word[MAX_WORD_LENGTH];
  int frequency;
  double probability;
} Node;


// for stable marriage
typedef struct Pair {
  int manRank;
  int womanRank;
} Pair;

// compare function for qsort
int compare(const void *a, const void *b);

// recursive function to traverse each table
void traverse(float cost[602][601], int root[602][601], char *pattern, Node *w, int n, int x);

// function to traverse sorted array for greedy technique
void greedy(Node *w, char *pattern, int start, int end, int *found);

void P11(); 

void P12();

void P2();
