
/* 
NAME: MANEESH WIJEWARDHANA
ID: 1125828
COURSE: CIS*3490
DUE DATE: MARCH 28

ASSIGNMENT 4
*/ 
#include "A4Header.h"

void P2() {
  char filename[100] = "";
  char buff[256];
  printf("Enter filename: ");
  scanf("%s", filename);
  FILE *fp = fopen(filename, "r");

  // check for invalid file
  if (fp == NULL) {
    printf("Could not open file\n");
    return;
    fclose(fp);
  }

  int n = 0;
  // get n value from file
  fscanf(fp, "%d", &n);
  int Marr[n][n];
  int Warr[n][n];
  // populate men array with men
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fscanf(fp, "%d", &Marr[i][j]);
    }
  }
  // skip new line
  fgets(buff, sizeof(buff), fp);
  // populate women array with women
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fscanf(fp, "%d", &Warr[i][j]);
    }
  }
  /*// double check arrays*/
  /*printf("Men array\n");*/
  /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++) {*/
      /*printf("%d ", Marr[i][j]);*/
    /*}*/
    /*printf("\n");*/
  /*}*/
  /*printf("Women array\n");*/
  /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++) {*/
      /*printf("%d ", Warr[i][j]);*/
    /*}*/
    /*printf("\n");*/
  /*}*/
  fclose(fp);

  // making ranking table
  Pair ranking[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if (Marr[i][k] == j + 1) {
          ranking[i][j].manRank = k + 1;
        }
        if (Warr[j][k] == i + 1) {
          ranking[i][j].womanRank = k + 1;
        }
      }
    }
  }
  // double check ranking table
  /*printf("Ranking Matrix\n");*/
  /*for (int i = 0; i < n; i++) {*/
    /*for (int j = 0; j < n; j++) {*/
      /*printf("(%d %d)", ranking[i][j].manRank, ranking[i][j].womanRank);*/
    /*}*/
    /*printf("\n");*/
  /*}*/
  // now start algorithm for matching
  // start with all men and women free
  int match[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      match[i][j] = 0;
    }
  }
  int womenPartner[n];
  bool manFree[n];
  int freeCount = n;
  // init all to free
  for (int i = 0; i < n; i++) {
    womenPartner[i] = -1;
    manFree[i] = false;
  }
  // start matching process
  while (freeCount > 0) {
    // find a free man arbitrarily
    int m;
    for (m = 0; m < n; m++) {
      if (manFree[m] == false) {
        break;
      }
    }
    // go through women preferences where m is the free man picked
    for (int i = 0; i < n && manFree[m] == false; i++) {
      int w = Marr[m][i];
      // if women is free, engage but not married
      if (womenPartner[w - 1] == -1) {
        womenPartner[w - 1] = m;
        match[m][w - 1] = 1;
        manFree[m] = true;
        freeCount--;
      } else { // if w is not free
        // get current engagement of w
        int tempMan = womenPartner[w - 1];
        bool ret = false;
        // go through ranking table to find if m is better than tempMan
        // if m is better, then replace tempMan with m
        // if m is not better, then continue
        if (ranking[tempMan][w - 1].womanRank < ranking[m][w - 1].womanRank) {
          match[tempMan][w - 1] = 1;
          ret = true;
        } else {
          match[m][w - 1] = 1;
          match[tempMan][w - 1] = 0;
          ret = false;
        }
        if (ret == false) {
          womenPartner[w - 1] = m;
          manFree[m] = true;
          manFree[tempMan] = false;
        }
      }
    }
  }
  printf("Matching Matrix\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", match[i][j]);
    }
    printf("\n");
  }
}
