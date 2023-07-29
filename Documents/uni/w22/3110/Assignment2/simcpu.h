/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
COURSE: CIS*3110 ASSIGNMENT 2 - CPU SCHEDULER
DUE DATE: MARCH 19
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// burst struct
typedef struct Burst {
    int burstNumber;
    int cpuTime;
    int ioTime;
    struct Burst *next;
} Burst;

// thread struct
typedef struct node {
    int process;
    int thread;
    int arrivalTime;
    int updatedArrivalTime;
    int currCPUTime;
    int currIOTime;
    int numberOfBursts;
    int currNumberOfBursts;
    Burst *b;
    int finishTime;
    int turnaround;
    struct node *next;
} Thread;
