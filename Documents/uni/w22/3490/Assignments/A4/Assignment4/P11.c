/* 
NAME: MANEESH WIJEWARDHANA
ID: 1125828
COURSE: CIS*3490
DUE DATE: MARCH 28

ASSIGNMENT 4
*/ 
#include "A4Header.h"
#include <stdlib.h>

// compare function for qsort
int compare(const void *a, const void *b) {
  Node *x = (Node *)a;
  Node *y = (Node *)b;
  return strcmp(x->word, y->word);
}

// recursive function to traverse each table
void traverse(float cost[602][601], int root[602][601], char *pattern, Node *w, int n, int x) {
  int k;
  k = root[x][n];
  int i = k - 1;
  if (k == 0) {
    printf("Not found\n");
    return;
  } 
  if (strcmp(pattern, w[i].word) < 0) {
    printf("Compared with %s (%.3f), go left subtree.\n", w[i].word, cost[x][n]);
    traverse(cost, root, pattern, w, k - 1, x);
  } else if (strcmp(pattern, w[i].word) > 0) {
    printf("Compared with %s (%.3f), go right subtree.\n", w[i].word, cost[x][n]);
    traverse(cost, root, pattern, w, n, k + 1);
  } else if (strcmp(pattern, w[i].word) == 0) {
    printf("Compared with %s (%.3f), found.\n", w[i].word, cost[x][n]);
  } else {
    printf("Not found\n");
  }
}

void P11() {
  char buff[256];
  FILE *fp = fopen("data_A4_Q1.txt", "r");
  // check for invalid file
  if (fp == NULL) {
    printf("Error opening file\n");
    fclose(fp);
    return;
  }
  // allocate space for the words
  Node *w = malloc(sizeof(Node) * 100000);
  int z = 0;
  char *token;
  // parse file and store words
  while (fgets(buff, sizeof(buff), fp)) {
    strtok(buff, "\n");
    token = strtok(buff, " ");
    while (token != NULL) {
      strcpy(w[z].word, token);
      token = strtok(NULL, " ");
      z++;
    }
    /*printf("%d %s\n", i, w[i - 1].word);*/
  }
  fclose(fp);
  // get frequency of each word in the file
  /*int frequency[z];*/
  for (int j = 0; j < z; j++) {
    for (int k = 0; k < z; k++) {
      if (strcmp(w[j].word, w[k].word) == 0) {
        w[j].frequency++;
      }
    }
    /*frequency[j] = w[j].frequency;*/
  }
  // get the probability of each word
  // and store it in probability
  for (int j = 0; j < z; j++) {
    w[j].probability = (double)w[j].frequency / z;
  }
  // remove duplicates from the array of words and their frequencies and their probabilities 
  // and sort the array in ascending order
  qsort(w, z, sizeof(Node), compare);
  int k = 0;
  for (int j = 0; j < z; j++) {
    if (strcmp(w[j].word, w[j + 1].word) != 0) {
      w[k] = w[j];
      k++;
    }
  }
  z = k;
  int n = z;
  // print the words and their frequencies and their probabilities
  /*for (int j = 0; j < n; j++) {*/
    /*printf("%d %s %d %.3f\n", j, w[j].word, w[j].frequency, w[j].probability);*/
  /*}*/
  /*printf("Number of unique words: %d\n", n);*/
  // create the cost table and root table from textbook algo
  float cost[n + 2][n + 1];
  int root[n + 2][n + 1];
  for (int i = 1; i <= n; i++) {
    cost[i][i - 1] = 0;
    cost[i][i] = w[i - 1].probability;
    root[i][i] = i;
  }
  cost[n + 1][n] = 0;
  for (int d = 1; d <= n - 1; d++) {
    for (int i = 1; i <= n - d; i++) {
      int j = i + d;
      float minval = INFINITY;
      int kmin = INT_MAX;
      for (int k = i; k <= j; k++) {
        if (cost[i][k - 1] + cost[k + 1][j] < minval) {
          minval = cost[i][k - 1] + cost[k + 1][j];
          kmin = k;
        }
      }
      root[i][j] = kmin;
      float sum = w[i - 1].probability;
      for (int s = i + 1; s <= j; s++) {
        sum += w[s - 1].probability;
      }
      cost[i][j] = minval + sum;
    }
  }
  // print to check
  /*for (int i = 1; i <= 3; i++) {*/
    /*for (int j = 0; j < n + 1; j++) {*/
      /*printf("%.2f ", cost[i][j]);*/
    /*}*/
    /*printf("\n");*/
  /*}*/
  /*for (int i = 1; i <= 3; i++) {*/
    /*for (int j = 0; j < n + 1; j++) {*/
      /*printf("%d ", root[i][j]);*/
    /*}*/
    /*printf("\n");*/
  /*}*/
  // prompt
  char *pattern = malloc(sizeof(char) * 10000);
  printf("Enter a pattern: ");
  scanf("%s", pattern);
  // search for the pattern
  traverse(cost, root, pattern, w, n, 1);
}

