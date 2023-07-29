/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
EMAIL: mkandage@uoguelph.ca
COURSE: CIS*3110
DUE DATE: APRIL 7, 2022

ASSIGNMENT 3 - MEMORY MANAGEMENT
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// the process structure
typedef struct Process {
    int id;
    int size;
    int swaps;
    struct Process *next;
} Process;

// add to queue to the end
void enqueue(Process *proc, Process **head);

// remove from queue
Process *dequeue(Process **head);

// check if queue is empty
bool isEmpty(Process *head);

// create a new process
Process *createProcess(int id, int size);

// get last memory block
Process *getLast();

// print queue
void printQueue(Process *head);

