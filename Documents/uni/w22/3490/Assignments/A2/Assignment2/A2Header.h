/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: FEB 14, 2022
COURSE: CIS*3490

ASSIGNMENT 2 - HEADER FILE FOR COUNTING INVERSIONS AND FINDING SHORTEST PATH AROUND

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

typedef struct Point {
  double x;
  double y;
} Point;

// file opening and calling of helper functions
int bruteForceInversions();

// file opening and calling of helper functions
int mergeSortInversions();

int merge(int arr[], int temp[], int left, int mid, int right);
int mergeSort(int arr[], int temp[], int left, int right);

// file opening and calling of helper functions
int bruteForceConvexHull();

// Calculates the hull in a brute force approach
int calcBruteForceHull(Point p[], Point brutePoints[], int count);

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point points[], int p, int q, int r);

// file opening and calling of helper functions
int quickConvexHull();

// finds the hull using quicksort method
int getHull(Point *points, Point *quickPoints, Point p1, Point p2, int count, int hullCounter, int side);

// this function returns the hull counter using getHull
int quickHull(Point *points, Point *quickPoints, int count);

// Returns the side of point p with respect to line joining points p1 and p2.
int getSide(Point p1, Point p2, Point p);

// returns a value proportional to the distance between the point p and the line joining the points p1 and p2
int lineDistance(Point p1, Point p2, Point p);

