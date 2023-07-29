/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: FEB 14, 2022
COURSE: CIS*3490

ASSIGNMENT 2 - FINDING SHORTEST PATH AROUND

*/

#include "A2Header.h"

int orientation(Point brutePoints[], int p, int q, int r) {
  int val = (brutePoints[q].y - brutePoints[p].y) * (brutePoints[r].x - brutePoints[q].x) - (brutePoints[q].x - brutePoints[p].x) * (brutePoints[r].y - brutePoints[q].y);
  if (val == 0) {
    return 0; // collinear
  } else if (val > 0) {
    return 1; // clockwise
  } else {
    return 2; // counterclockwise
  }
}

int calcBruteForceHull(Point points[], Point brutePoints[], int count) {
  // counts number of bounding points in the convex hull set
  int h = 0; 
  // create line from Point I to Point J
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < count; j++) {
      if (i == j || (points[i].x == points[j].x && points[i].y == points[j].y)) {
        continue; // skip because same point
      } 
      bool isLeft = true; // reset
      // if all other points are on the left or in-line, then it's a bounding point
      for(int k = 0; k < count; k++) {
        if ( k == i || k == j || (points[k].x == points[i].x && points[k].y == points[i].y) || (points[k].x == points[j].x && points[k].y == points[j].y)) {
          continue; // skip because same point
        } 
        // calc and check which side of line Point K is on
        double d = (points[k].x - points[i].x) * (points[j].y - points[i].y) - (points[k].y - points[i].y) * (points[j].x - points[i].x);
        if (d >= 0) { // don't want RS or in-line
          isLeft = false;
          break;
        }
      }
      // if that passes, add both to bounding set
      if (isLeft == true) {
        // printf("Point %d: %.1f, %.1f\n", h + 1, points[i].x, points[i].y);
        bool isUnique = true;
        bool isUnique2 = true;
        // check for dupes
        for (int m = 0; m < h; m++) {
          if (points[i].x == brutePoints[m].x && points[i].y == brutePoints[m].y) {
            isUnique = false;
          } 
          if (points[j].x == brutePoints[m].x && points[j].y == brutePoints[m].y) {
            isUnique2 = false;
          } 
        }
        // then add
        if (isUnique == true) {
          brutePoints[h] = points[i];
          h++;
        } 
        if (isUnique2 == true) {
          brutePoints[h] = points[j];
          h++;
        } 
      }
    }
  }
  return h;
}

int bruteForceConvexHull() {
  char buff[256];
  char *token;

  FILE* fp = fopen("data_A2_Q2.txt", "r");

  if (fp == NULL) {
    printf("Could not open file\n");
    return -1;
  }

  int i = 0;
  Point points[30000];
  // parse each line in file
  while (fgets(buff, sizeof(buff), fp)) {
    // remove newline
    strtok(buff, "\n");
    // split on comma then space
    token = strtok(buff, ", ");
    // add first value to x in struct
    points[i].x = atof(token);
    token = strtok(NULL, ", ");
    // add second value to y in struct
    points[i].y = atof(token);
    // printf("%.1f, %.1f\n", points[i].x, points[i].y); 
    i++;
  }   

  // check that min size requirements are met
  if (i < 3) {
    fprintf(stderr, "\nInvalid: Convex hull not possible - must have at least 3 points\n");
    return -1;
  }

  Point brutePoints[i];

  clock_t begin = clock();
  int result = calcBruteForceHull(points, brutePoints, i);
  clock_t end = clock();

  // printing points
  printf("The points in the hull...\n");
  for (int i = 0; i < result; i++) {
    printf("Point %d: %.1f, %.1f\n", i + 1, brutePoints[i].x, brutePoints[i].y);
  }
  double timeSeconds = (double)(end - begin) / CLOCKS_PER_SEC;
  int timeMille = 1000 * timeSeconds;
  printf("Time for computing hull: %dms\n", timeMille);

  // user input these
  Point s1; 
  Point s2;
  printf("Enter x and y coord of s1 (num num): ");
  scanf("%lf %lf", &s1.x, &s1.y);
  printf("Enter x and y coord of s2 (num num): ");
  scanf("%lf %lf", &s2.x, &s2.y);
  // printf("You chose s1: %.1f, %.1f\ns2: %.1f, %.1f\n", s1.x, s1.y, s2.x, s2.y);

  Point shortestBrutePoints[result]; // result is my hull count which is 22
  int initialP = 0;
  int endP = 0;

  // saving indices of start and end points
  for (int i = 1; i < result; i++) { 
    if (brutePoints[i].x == s1.x && brutePoints[i].y == s1.y) {
      initialP = i;
    }
    if (brutePoints[i].x == s2.x && brutePoints[i].y == s2.y) {
      endP = i;
    }
  }

  // printf("Start index: %d\n", initialP);
  // printf("End index: %d\n", endP);

  // Start from leftmost point, keep moving clockwise until reach the start point again
  int startPoint = initialP;
  int temp;
  int newIndex = 0;
  do {
    shortestBrutePoints[newIndex].x = brutePoints[startPoint].x;
    shortestBrutePoints[newIndex].y = brutePoints[startPoint].y;
    // printf("TEST: %.1f, %.1f\n", shortestBrutePoints[newIndex].x, shortestBrutePoints[newIndex].y);

    // next clockwise point
    temp = (startPoint + 1) % result;

    // update temp to next clockwise point we find
    for (int y = 0; y < result; y++) {
      if (orientation(brutePoints, startPoint, y, temp) == 1) {
        temp = y;
      }
    }
    // after loop, we have next clockwise point with respect to starting point
    // set starting point as temp and look for next point to be added
    startPoint = temp;
    newIndex++;
  } while (startPoint != endP);
  shortestBrutePoints[newIndex].x = brutePoints[startPoint].x;
  shortestBrutePoints[newIndex].y = brutePoints[startPoint].y;
  newIndex++;

  // Now start from leftmost point, keep moving counterclockwise until reach the start point again
  int startPoint2 = initialP;
  int temp2;
  int newIndex2 = 0;
  do {
    shortestBrutePoints[newIndex2].x = brutePoints[startPoint2].x;
    shortestBrutePoints[newIndex2].y = brutePoints[startPoint2].y;
    // printf("TEST: %.1f, %.1f\n", shortestBrutePoints[newIndex].x, shortestBrutePoints[newIndex].y);
    
    // next counterclockwise point
    temp2 = (startPoint2 + 1) % result;

    // update temp to next counterclockwise point we find
    for (int y = 0; y < result; y++) {
      if (orientation(brutePoints, startPoint2, y, temp2) == 2) {
        temp2 = y;
      }
    }
    // after loop, we have next counterclockwise point with respect to starting point
    // set starting point as temp and look for next point to be added
    startPoint2 = temp2;
    newIndex2++;
  } while (startPoint2 != endP);
  shortestBrutePoints[newIndex2].x = brutePoints[startPoint2].x;
  shortestBrutePoints[newIndex2].y = brutePoints[startPoint2].y;
  newIndex2++;

  // now calculate distance for each path using formula on pdf
  // s1 = x1,y1 
  // s2 = x2,y2
  // sqrt((x1-x2)^2 + (y1-y2)^2)
  double distance1 = 0;
  for (int d = 0; d < newIndex - 1; d++) {
    distance1 += sqrt(((shortestBrutePoints[d].x - shortestBrutePoints[d + 1].x) * (shortestBrutePoints[d].x - shortestBrutePoints[d + 1].x)) + ((shortestBrutePoints[d].y - shortestBrutePoints[d + 1].y) * (shortestBrutePoints[d].y - shortestBrutePoints[d + 1].y)));
  }

  double distance2 = 0;
  for (int d = 0; d < newIndex2 - 1; d++) {
    distance2 += sqrt(((shortestBrutePoints[d].x - shortestBrutePoints[d + 1].x) * (shortestBrutePoints[d].x - shortestBrutePoints[d + 1].x)) + ((shortestBrutePoints[d].y - shortestBrutePoints[d + 1].y) * (shortestBrutePoints[d].y - shortestBrutePoints[d + 1].y)));
  }

  // comparing the two distances and returning the shortest one with its number of points and points themselves
  if (distance1 < distance2) {
    printf("The number of points on the shortest path: %d\n", newIndex);
    printf("Distance: %.1f\n", distance1);
    printf("The points on the path: \n");
    for (int z = 0; z < newIndex; z++) {
      printf("(%.1f, %.1f)\n", shortestBrutePoints[z].x, shortestBrutePoints[z].y);
    }
    return newIndex;
  } else {
    printf("The number of points on the shortest path: %d\n", newIndex2);
    printf("Distance: %.1f\n", distance2);
    printf("The points on the path: \n");
    for (int z = 0; z < newIndex2; z++) {
      printf("(%.1f, %.1f)\n", shortestBrutePoints[z].x, shortestBrutePoints[z].y);
    }
    return newIndex2;
  }
  // test with 484.1 6266.3 and 6434.5 1065.1
}
