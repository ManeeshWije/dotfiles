/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: FEB 14, 2022
COURSE: CIS*3490

ASSIGNMENT 2 - FINDING SHORTEST PATH AROUND

*/

#include "A2Header.h"

// endpoints are p1 and p2 and side could be 1 or -1
int getHull(Point *points, Point *quickPoints, Point p1, Point p2, int count, int hullCount, int whichSide) {
  int index = 0;
  int maxDistance = 0;
  // finding max distance
  for (int i = 0; i < count; i++) {
    int dist = lineDistance(points[i], p1, p2);
    // int dist = fabs((points[i].x - p1.x) * (p2.y - p1.y) - (points[i].y - p1.y) * (p2.x - p1.x));
    if (getSide(p1, p2, points[i]) == whichSide && dist > maxDistance) {
      index = i;
      maxDistance = dist;
    }
  }
  // If no point is found, add the end points
  if (index == 0) {
    bool isP1 = false;
    bool isP2 = false;
    if (hullCount == 0) {
      quickPoints[hullCount] = p1;
      hullCount++;
      quickPoints[hullCount] = p2;
      hullCount++;
    } else {
      int j;
      for (j = 0; j < hullCount; j++) {
        if (p1.x == quickPoints[j].x && p1.y == quickPoints[j].y) {
          isP1 = true;
        }
        if (p2.x == quickPoints[j].x && p2.y == quickPoints[j].y) {
          isP2 = true;
        }
      }
      if (isP1 == false) {
        quickPoints[hullCount] = p1;
        hullCount++;
      }
      if (isP2 == false) {
        quickPoints[hullCount] = p2;
        hullCount++;
      }
    }
    return hullCount;
  }
  // recurse for two parts divided
  hullCount = getHull(points, quickPoints, points[index], p1, count, hullCount, -getSide(points[index], p1, p2));
  hullCount = getHull(points, quickPoints, points[index], p2, count, hullCount, -getSide(points[index], p2, p1));
  return hullCount;
}

int quickConvexHull() {
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
    // set first number as x in struct
    points[i].x = atof(token);
    token = strtok(NULL, ", ");
    // set second number as y in struct
    points[i].y = atof(token);
    // printf("%.1f, %.1f\n", points[i].x, points[i].y); 
    i++;
  }   

  // check that min size requirements are met
  if (i < 3) {
    fprintf(stderr, "\nInvalid: Convex hull not possible - must have at least 3 points\n");
    return -1;
  }

  int j;
  int min = 0;
  int max = 0;
  for (j = 1; j < i; j++) {
    if (points[j].x < points[min].x) {
      min = j;
    }
    if (points[j].x > points[max].x) {
      max = j;
    }
  }
  Point quickPoints[i];
  int result = 0;
  clock_t begin = clock();
  // recurse and find hull count on first side of line
  result = getHull(points, quickPoints, points[min], points[max], i, result, 1);

  // recurse and find hull count on second side of line
  result = getHull(points, quickPoints, points[min], points[max], i, result, -1);
  clock_t end = clock();

  printf("Points in the hull...\n");
  for (int k = 0; k < result; k++) {
    printf("Point %d: (%.1f, %.1f)\n", k + 1, quickPoints[k].x, quickPoints[k].y);
  }
  double timeSeconds = (double)(end - begin) / CLOCKS_PER_SEC;
  int timeMille = 1000 * timeSeconds;
  printf("Time for computing hull: %dms\n", timeMille);

  /*
  EVERYTHING AFTER HERE IS THE SAME ALGORITHM USED IN P21 TO FIND SHORTEST PATH AROUND
  */

  // points which user inputs
  Point s1;
  Point s2;
  printf("Enter x and y coord of s1 (num num): ");
  scanf("%lf %lf", &s1.x, &s1.y);
  printf("Enter x and y coord of s2 (num num): ");
  scanf("%lf %lf", &s2.x, &s2.y);
  // printf("You chose s1: %.1f, %.1f\ns2: %.1f, %.1f\n", s1.x, s1.y, s2.x, s2.y);

  Point shortestQuickPoints[result]; // result is my hull count which is 22
  int initialP = 0;
  int endP = 0;

  // saving indices of start and end points
  for (int i = 1; i < result; i++) { 
    if (quickPoints[i].x == s1.x && quickPoints[i].y == s1.y) {
      initialP = i;
    }
    if (quickPoints[i].x == s2.x && quickPoints[i].y == s2.y) {
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
    shortestQuickPoints[newIndex].x = quickPoints[startPoint].x;
    shortestQuickPoints[newIndex].y = quickPoints[startPoint].y;
    // printf("TEST: %.1f, %.1f\n", shortestQuickPoints[newIndex].x, shortestQuickPoints[newIndex].y);

    // next clockwise point
    temp = (startPoint + 1) % result;

    // update temp to next clockwise point we find
    for (int y = 0; y < result; y++) {
      if (orientation(quickPoints, startPoint, y, temp) == 1) {
        temp = y;
      }
    }
    // after loop, we have next clockwise point with respect to starting point
    // set starting point as temp and look for next point to be added
    startPoint = temp;
    newIndex++;
  } while (startPoint != endP);
  shortestQuickPoints[newIndex].x = quickPoints[startPoint].x;
  shortestQuickPoints[newIndex].y = quickPoints[startPoint].y;
  newIndex++;

  // Now start from leftmost point, keep moving counterclockwise until reach the start point again
  int startPoint2 = initialP;
  int temp2;
  int newIndex2 = 0;
  do {
    shortestQuickPoints[newIndex2].x = quickPoints[startPoint2].x;
    shortestQuickPoints[newIndex2].y = quickPoints[startPoint2].y;
    // printf("TEST: %.1f, %.1f\n", shortestQuickPoints[newIndex].x, shortestQuickPoints[newIndex].y);
    
    // next counterclockwise point
    temp2 = (startPoint2 + 1) % result;

    // update temp to next counterclockwise point we find
    for (int y = 0; y < result; y++) {
      if (orientation(quickPoints, startPoint2, y, temp2) == 2) {
        temp2 = y;
      }
    }
    // after loop, we have next counterclockwise point with respect to starting point
    // set starting point as temp and look for next point to be added
    startPoint2 = temp2;
    newIndex2++;
  } while (startPoint2 != endP);
  shortestQuickPoints[newIndex2].x = quickPoints[startPoint2].x;
  shortestQuickPoints[newIndex2].y = quickPoints[startPoint2].y;
  newIndex2++;

  // now calculate distance for each path using formula on pdf
  // s1 = x1,y1 
  // s2 = x2,y2
  // sqrt((x1-x2)^2 + (y1-y2)^2)
  double distance1 = 0;
  for (int d = 0; d < newIndex - 1; d++) {
    distance1 += sqrt(((shortestQuickPoints[d].x - shortestQuickPoints[d + 1].x) * (shortestQuickPoints[d].x - shortestQuickPoints[d + 1].x)) + ((shortestQuickPoints[d].y - shortestQuickPoints[d + 1].y) * (shortestQuickPoints[d].y - shortestQuickPoints[d + 1].y)));
  }

  double distance2 = 0;
  for (int d = 0; d < newIndex2 - 1; d++) {
    distance2 += sqrt(((shortestQuickPoints[d].x - shortestQuickPoints[d + 1].x) * (shortestQuickPoints[d].x - shortestQuickPoints[d + 1].x)) + ((shortestQuickPoints[d].y - shortestQuickPoints[d + 1].y) * (shortestQuickPoints[d].y - shortestQuickPoints[d + 1].y)));
  }

  // comparing the two distances and returning the shortest one with its number of points and points themselves
  if (distance1 < distance2) {
    printf("The number of points on the shortest path: %d\n", newIndex);
    printf("Distance: %.1f\n", distance1);
    printf("The points on the path: \n");
    for (int z = 0; z < newIndex; z++) {
      printf("(%.1f, %.1f)\n", shortestQuickPoints[z].x, shortestQuickPoints[z].y);
    }
    return newIndex;
  } else {
    printf("The number of points on the shortest path: %d\n", newIndex2);
    printf("Distance: %.1f\n", distance2);
    printf("The points on the path: \n");
    for (int z = 0; z < newIndex2; z++) {
      printf("(%.1f, %.1f)\n", shortestQuickPoints[z].x, shortestQuickPoints[z].y);
    }
    return newIndex2;
  }
  // test with 484.1 6266.3 and 6434.5 1065.1
}

int getSide(Point p1, Point p2, Point p) {
  int num = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
  if (num > 0) {
    return 1;
  }
  if (num < 0) {
    return -1;
  }
  return 0;
}

int lineDistance(Point p1, Point p2, Point p) {
  return fabs((p.y - p1.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p.x - p1.x));
}


