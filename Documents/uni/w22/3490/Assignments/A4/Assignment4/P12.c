/* 
NAME: MANEESH WIJEWARDHANA
ID: 1125828
COURSE: CIS*3490
DUE DATE: MARCH 28

ASSIGNMENT 4
*/ 
#include "A4Header.h"

void greedy(Node *w, char *pattern, int start, int end, int *found) {
  // base cases
  if (start > end || *found) {
    return;
  }
  float maxProb = 0;
  int i = start;
  int jIndex = 0;;
  // find the max probability
  while (i <= end) {
    if (w[i].probability > maxProb) {
      maxProb = w[i].probability;
      jIndex = i;
    }
    i++;
  }
  // compare words and go left or right based on condition
  if (strcmp(pattern, w[jIndex].word) < 0) {
    printf("Compared with %s (%.3f), go left subtree.\n", w[jIndex].word, w[jIndex].probability);
    greedy(w, pattern, start, jIndex - 1, found);
  } else if (strcmp(pattern, w[jIndex].word) > 0) {
    printf("Compared with %s (%.3f), go right subtree.\n", w[jIndex].word, w[jIndex].probability);
    greedy(w, pattern, jIndex + 1, end, found);
  } else if (strcmp(pattern, w[jIndex].word) == 0) {
    *found = 1;
    printf("Compared with %s (%.3f), found.\n", w[jIndex].word, w[jIndex].probability);
  } else {
    printf("Not found\n");
  }
}

void P12() {
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
  // and store it in frequency
  // and store the word in word
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
  // prompt
  char *pattern = malloc(sizeof(char) * 10000);
  printf("Enter a pattern: ");
  scanf("%s", pattern);
  // search for the pattern
  int found = 0;
  greedy(w, pattern, 0, n - 1, &found);
  if (found == 0) {
    printf("Not found\n");
  }
}
