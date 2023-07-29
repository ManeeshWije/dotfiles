/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
COURSE: CIS*3110 ASSIGNMENT 2 - CPU SCHEDULER
DUE DATE: MARCH 19
*/

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functions for priority queue
// referenced from
// https://www.geeksforgeeks.org/priority-queue-using-linked-list/

// create a new thread
Thread *newThread(Thread newthread) {
  // calloc and set all values
  Thread *tempThread = calloc(1, sizeof(Thread));
  /*tempThread = &newthread;*/
  tempThread->thread = newthread.thread;
  tempThread->process = newthread.process;
  tempThread->arrivalTime = newthread.arrivalTime;
  tempThread->updatedArrivalTime = newthread.updatedArrivalTime;
  tempThread->currCPUTime = newthread.currCPUTime;
  tempThread->currIOTime = newthread.currIOTime;
  tempThread->b = newthread.b;
  tempThread->numberOfBursts = newthread.numberOfBursts;
  tempThread->currNumberOfBursts = newthread.currNumberOfBursts;
  tempThread->finishTime = newthread.finishTime;
  tempThread->turnaround = newthread.turnaround;
  tempThread->next = NULL;
  return tempThread;
}

// return value at head
Thread peek(Thread **head) { return (**head); }

// Removes the element with the highest priority form the list
void pop(Thread **head) {
  Thread *tempThread = *head;
  (*head) = (*head)->next;
  free(tempThread);
}

// Function to push according to priority
void push(Thread **head, Thread newthread) {
  Thread *begin = (*head);
  // create a new thread
  Thread *tempThread = newThread(newthread);
  // if head has lesser priority than new, insert new before head and change
  // head
  if ((*head)->updatedArrivalTime > newthread.updatedArrivalTime) {
    // insert
    tempThread->next = *head;
    (*head) = tempThread;
  } else { // else traverse and find insertion point
    while (begin->next != NULL && begin->next->updatedArrivalTime < newthread.updatedArrivalTime) {
      begin = begin->next;
    }
    tempThread->next = begin->next;
    begin->next = tempThread;
  }
}

// Function to check is list is empty
int isEmpty(Thread **head) { return (*head) == NULL; }
