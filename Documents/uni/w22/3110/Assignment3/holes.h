/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
EMAIL: mkandage@uoguelph.ca
COURSE: CIS*3110
DUE DATE: APRIL 7, 2022

ASSIGNMENT 3 - MEMORY MANAGEMENT
*/
#include "queue.h"

// swap processes out of memory and into queue
void swap(Process **head);

// main function for first fit
void first(char *filename, char *flag);
// first fit algorithm
// we wil use the return value of the function to determine if we need to swap out a process or not 
int addFirst(Process **head);

// main function for best fir
void best(char *filename, char *flag);
// best fit algorithm
// we wil use the return value of the function to determine if we need to swap out a process or not 
int addBest(Process **head);

// main function for worst fit
void worst(char *filename, char *flag);
// worst fit algorithm
// we wil use the return value of the function to determine if we need to swap out a process or not 
int addWorst(Process **head);

// main function for next fit
void next(char *filename, char *flag);
// next fit algorithm
// we wil use the return value of the function to determine if we need to swap out a process or not 
int addNext(Process **head);

