/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
COURSE: CIS*3110 ASSIGNMENT 2 - CPU SCHEDULER
DUE DATE: MARCH 19
*/

#include "simcpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new thread
Thread *newThread(Thread newthread);

// Return value at head
Thread peek(Thread **head);

// Removes the element with the highest priority form the list
void pop(Thread **head);

// Function to push according to priority
void push(Thread **head, Thread newthread);

// Function to check if list is empty
int isEmpty(Thread **head);

