/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
EMAIL: mkandage@uoguelph.ca
COURSE: CIS*3110
DUE DATE: APRIL 7, 2022

ASSIGNMENT 3 - MEMORY MANAGEMENT
*/

#include "queue.h"

void enqueue(Process *proc, Process **head) {
  // start at the head of the queue
  if (*head == NULL) {
    *head = proc;
    (*head)->next = NULL;
  } else {
    // create temp
    Process *temp = *head;
    // traverse
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = proc;
    proc->next = NULL;
  }
}

Process *dequeue(Process **head) {
  // create temp
  Process *temp = *head;
  // check if list is empty
  // if empty return NULL, if not empty, set head to next
  // return temp
  if (*head == NULL) {
    return NULL;
  } else {
    *head = (*head)->next;
    temp->next = NULL;
    return temp;
  }
}

Process *createProcess(int id, int size) {
  Process *proc = (Process *)malloc(sizeof(Process));
  proc->id = id;
  proc->size = size;
  proc->next = NULL;
  return proc;
}

void printQueue(Process *head) {
  // create temp
  Process *temp = head;
  // traverse the list
  while (temp != NULL) {
    printf("id: %d, size: %d\n", temp->id, temp->size);
    temp = temp->next;
  }
}

bool isEmpty(Process *head) {
  if (head == NULL) {
    return true;
  }
  return false;
}
