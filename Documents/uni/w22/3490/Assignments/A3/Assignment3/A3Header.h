/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
DUE DATE: MARCH 14, 2022
COURSE: CIS*3490

ASSIGNMENT 3 - FUNCTION PROTOTYPES AND HEADERS

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <ctype.h>

/*
ALL FUNCS RETURN 0 BUT HAVE PRINTS IN THEM FOR THE ANSWERS
*/

// function to get most common point and max number of intervals in a brute force approach
// prints common point, max number of intervals, and execution time for calculation
int bruteIntervals();

// function to get most common point and max number of intervals using a presorting technique
// prints common point, max number of intervals, and execution time for calculation
int presortIntervals();

// function to search for a specific string in a brute force approach
// prints count, number of shifts, and execution time for searching
int bruteStringSearch();

// function for shiftable for horspool
void shiftTable(char[], int[]);

// function that utilizes a shift table to find the number of occurances of a string
// as well as the number of shifts taken
int horspoolStringSearch();

// similar to shiftable but for bad chars
void badCharHeuristic(char *str, int size, int badChar[256]);

// function that utilizes a badchar heuristic table to find the number of occurances of a string
// as well as the number of shifts taken
int boyerMooreStringSearch();
