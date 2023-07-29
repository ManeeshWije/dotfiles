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

void FCFS(int detailed, int verbose) {
  int numberOfProcesses = 0; // number of processes
  int threadSwitch = 0; // time units required to switch to a new thread 
  int processSwitch = 0; // time units required to switch to a new thread in a diff process

  int numberOfThreads = 0; // number of threads

  int cpuBursts = 0; // cpu execution bursts that each thread requires

  // cpu burst variables
  int burstsNum = 0;
  int cpuTime = 0;
  int ioTime = 0;

  // total vars to add up to
  int totalNumThreads = 0;

  // priority queue
  Thread *pq = NULL;
  // flag to set queue made
  bool threadSet = false;

  // Parsing the file
  // first line
  Thread threadToAdd;
  scanf("%d %d %d", &numberOfProcesses, &threadSwitch, &processSwitch);
  for (int i = 0; i < numberOfProcesses; i++) {
    // second line
    scanf("%d %d", &threadToAdd.process, &numberOfThreads);
    // go thru burst
    for (int j = 0; j < numberOfThreads; j++) {
      scanf("%d %d %d", &threadToAdd.thread, &threadToAdd.arrivalTime, &cpuBursts);
      threadToAdd.b = calloc(1, sizeof(Burst) * cpuBursts);
      int k = 0;
      for (k = 0; k < cpuBursts - 1; k++) {
        // get info
        scanf("%d %d %d", &burstsNum, &cpuTime, &ioTime);
        threadToAdd.b[k].burstNumber = burstsNum;
        threadToAdd.b[k].cpuTime = cpuTime;
        threadToAdd.b[k].ioTime = ioTime;
      }
      // last bursts
      scanf("%d %d", &burstsNum, &cpuTime);
      threadToAdd.b[k].burstNumber = burstsNum;
      threadToAdd.b[k].cpuTime = cpuTime;
      threadToAdd.b[k].ioTime = 0;

      threadToAdd.currCPUTime = 0;
      threadToAdd.currIOTime = 0;
      threadToAdd.currNumberOfBursts = 0;
      threadToAdd.finishTime = 0;
      threadToAdd.turnaround = 0;

      // creating priority queue
      if (threadSet == false) {
        threadToAdd.updatedArrivalTime = threadToAdd.arrivalTime;
        threadToAdd.numberOfBursts = cpuBursts;
        pq = newThread(threadToAdd);
        // set flag as its the first thread made
        threadSet = true;
      } else if (pq != NULL) {
        threadToAdd.updatedArrivalTime = threadToAdd.arrivalTime;
        threadToAdd.numberOfBursts = cpuBursts;
        push(&pq, threadToAdd);
      }
      totalNumThreads += 1;
    }
  }

  // FCFS Algorithm 
  printf("FCFS Scheduling\n");
  // loop through queue 
  int *processTurnaround = calloc(1, sizeof(int) * numberOfProcesses);
  // set indexes of process for turnaround time to zero
  for (int i = 0; i < numberOfProcesses; i++) {
    processTurnaround[i] = 0;
  }
  // data to collect
  int currentTime = 0;
  int idleTime = 0;
  bool isFirstThread = false;
  int currentProcess = 0;
  int totalSwitch = 0;

  // save output for -d flag
  char *realDetailed = calloc(1, sizeof(char) * 10000);
  char detailedOutput[10000];
  // save output for -v flag
  char *realVerbose = calloc(1, sizeof(char) * 10000);
  char verboseOutput[10000];

  while (!isEmpty(&pq)) {
    Thread temp = peek(&pq);
    pop(&pq);
    // check if new arrival time is greater than current time 
    // if so, add difference to idle time as well as current time for next one
    sprintf(verboseOutput, "At time %d: Thread %d of Process %d moves from new to ready\n", currentTime, temp.thread, temp.process);
    strcat(realVerbose, verboseOutput);
    if (temp.updatedArrivalTime > currentTime) {
      idleTime += temp.updatedArrivalTime - currentTime;
      currentTime += temp.updatedArrivalTime - currentTime;
    }
    // now we know if it was the first thread
    if (isFirstThread == true) {
      if (temp.process != currentProcess) {
        totalSwitch += processSwitch;
        currentTime += processSwitch;
      } else {
        totalSwitch += threadSwitch;
        currentTime += threadSwitch;
      }
    }
    isFirstThread = true;
    currentProcess = temp.process;

    currentTime += temp.b[temp.currNumberOfBursts].cpuTime;
    temp.currCPUTime += temp.b[temp.currNumberOfBursts].cpuTime;
    temp.currNumberOfBursts += 1;

    if (temp.currNumberOfBursts != temp.numberOfBursts) {
      temp.currIOTime += temp.b[temp.currNumberOfBursts - 1].ioTime;
      temp.updatedArrivalTime = currentTime + temp.b[temp.currNumberOfBursts - 1].ioTime;
      sprintf(verboseOutput, "At time %d: Thread %d of Process %d moves from running to blocked\n", currentTime, temp.thread, temp.process);
      strcat(realVerbose, verboseOutput);
      if (pq != NULL) {
        push(&pq, temp);
      } else {
        pq = newThread(temp);
      }
    } else {
      sprintf(verboseOutput, "At time %d: Thread %d of Process %d moves from ready to running\n", currentTime, temp.thread, temp.process);
      strcat(realVerbose, verboseOutput);
      sprintf(detailedOutput, "thread %d of Process %d:\n", temp.thread, temp.process);
      strcat(realDetailed, detailedOutput);
      sprintf(detailedOutput, "\tarrivalTime: %d:\n", temp.arrivalTime);
      strcat(realDetailed, detailedOutput);
      sprintf(detailedOutput,"\tserviceTime: %d, I/OTime: %d, turnaroundTime: %d, finishTime: %d\n", temp.currCPUTime, temp.currIOTime, (currentTime - temp.arrivalTime), currentTime);
      strcat(realDetailed, detailedOutput);
      if ((currentTime - temp.arrivalTime) > processTurnaround[temp.process - 1]) {
        // set turnaround for that process
        processTurnaround[temp.process - 1] = currentTime;
      }
      temp.finishTime = currentTime;
      temp.turnaround = temp.finishTime - temp.arrivalTime;
      temp.updatedArrivalTime = (temp.process * 100) + temp.thread;
      sprintf(verboseOutput, "At time %d: Thread %d of Process %d moves from running to terminated\n", currentTime, temp.thread, temp.process);
      strcat(realVerbose, verboseOutput);
    }
  }
  // first already have total time
  // so now get the average turnaround time of the processes
  printf("Total Time Required = %d\n", currentTime);
  int totalTurnaround = 0;
  for (int i = 0; i < numberOfProcesses; i++) {
    totalTurnaround += processTurnaround[i];
  }
  free(processTurnaround);
  printf("Average Turnaround Time is %.1lf units\n", totalTurnaround / (double)numberOfProcesses);
  // util = total cpu time / total time
  printf("CPU Utilization is %.1lf%%\n", (currentTime - totalSwitch - idleTime) * 100 / ((double)currentTime));
  if (detailed == 1) {
    printf("%s", realDetailed);
  }
  if (verbose == 1) {
    printf("%s", realVerbose);
  }
}

// COPY PASTED FCFS PARSING
void RR(int verbose, int rrq, int detailed) {
  int numberOfProcesses = 0; // number of processes
  int threadSwitch = 0; // time units required to switch to a new thread 
  int processSwitch = 0; // time units required to switch to a new thread in a diff process

  int numberOfThreads = 0; // number of threads

  int cpuBursts = 0; // cpu execution bursts that each thread requires

  // cpu burst variables
  int burstsNum = 0;
  int cpuTime = 0;
  int ioTime = 0;

  // total vars to add up to
  int totalNumThreads = 0;

  // priority queue
  Thread *pq = NULL;
  // flag to set queue made
  bool threadSet = false;

  // Parsing the file
  // first line
  Thread threadToAdd;
  scanf("%d %d %d", &numberOfProcesses, &threadSwitch, &processSwitch);
  for (int i = 0; i < numberOfProcesses; i++) {
    // second line
    scanf("%d %d", &threadToAdd.process, &numberOfThreads);
    // go thru burst
    for (int j = 0; j < numberOfThreads; j++) {
      scanf("%d %d %d", &threadToAdd.thread, &threadToAdd.arrivalTime, &cpuBursts);
      threadToAdd.b = calloc(1, sizeof(Burst) * cpuBursts);
      int k = 0;
      for (k = 0; k < cpuBursts - 1; k++) {
        // get info
        scanf("%d %d %d", &burstsNum, &cpuTime, &ioTime);
        threadToAdd.b[k].burstNumber = burstsNum;
        threadToAdd.b[k].cpuTime = cpuTime;
        threadToAdd.b[k].ioTime = ioTime;
      }
      // last bursts
      scanf("%d %d", &burstsNum, &cpuTime);
      threadToAdd.b[k].burstNumber = burstsNum;
      threadToAdd.b[k].cpuTime = cpuTime;
      threadToAdd.b[k].ioTime = 0;

      threadToAdd.currCPUTime = 0;
      threadToAdd.currIOTime = 0;
      threadToAdd.currNumberOfBursts = 0;
      threadToAdd.finishTime = 0;
      threadToAdd.turnaround = 0;

      // creating priority queue
      if (threadSet == false) {
        threadToAdd.updatedArrivalTime = threadToAdd.arrivalTime;
        threadToAdd.numberOfBursts = cpuBursts;
        pq = newThread(threadToAdd);
        // set flag as its the first thread made
        threadSet = true;
      } else if (pq != NULL) {
        threadToAdd.updatedArrivalTime = threadToAdd.arrivalTime;
        threadToAdd.numberOfBursts = cpuBursts;
        push(&pq, threadToAdd);
      }
      totalNumThreads += 1;
    }
  }
  // RR Algorithm 
  printf("Round Robin Scheduling (quantum = %d time units)\n", rrq);
  // loop through queue 
  int *processTurnaround = calloc(1, sizeof(int) * numberOfProcesses);
  // set indexes of process for turnaround time to zero
  for (int i = 0; i < numberOfProcesses; i++) {
    processTurnaround[i] = 0;
  }
  // data to collect
  int currentTime = 0;
  int idleTime = 0;
  bool isFirstThread = false;
  int currentProcess = 0;
  int currentThread = 0;
  int totalSwitch = 0;

  // save output for -d flag
  char *realDetailed = calloc(1, sizeof(char) * 10000);
  char detailedOutput[10000];
  // save output for -v flag
  char *realVerbose = calloc(1, sizeof(char) * 10000);
  char verboseOutput[10000];

  // same as fcfs with changes to account for rrq
  while (!isEmpty(&pq)) {
    Thread temp = peek(&pq);
    pop(&pq);

    sprintf(verboseOutput, "At time %d: Thread %d of Process %d moves from new to ready\n", currentTime, temp.thread, temp.process);
    strcat(realVerbose, verboseOutput);

    if (temp.updatedArrivalTime > currentTime) {
      idleTime += temp.updatedArrivalTime - currentTime;
      currentTime += temp.updatedArrivalTime - currentTime;
    }

    int s = 0;
    if (isFirstThread == true) {
      if (temp.process != currentProcess) {
        s = processSwitch;
        totalSwitch += processSwitch;
        currentTime += processSwitch;
      }
      else if (currentThread != temp.thread) {
        s = threadSwitch;
        totalSwitch += threadSwitch;
        currentTime += threadSwitch;
      }
      if (currentProcess == temp.process) {
        if (currentThread == temp.thread) {
          s = 0;
          totalSwitch += s;
        } 
      }
    }
    currentProcess = temp.process;
    currentThread = temp.thread;
    isFirstThread = true;

    // change for RR 
    bool burstFlag = false;
    int subtraction = 0;

    temp.b[temp.currNumberOfBursts].cpuTime -= rrq;
    //save remainder
    if (temp.b[temp.currNumberOfBursts].cpuTime < 0) {
      subtraction = temp.b[temp.currNumberOfBursts].cpuTime * -1;
      currentTime += rrq - subtraction;
      temp.currCPUTime += rrq - subtraction;
      temp.currNumberOfBursts++;
      burstFlag = true;
    }
    else if (temp.b[temp.currNumberOfBursts].cpuTime >= 0) {
      currentTime += rrq - subtraction;
      temp.currCPUTime += rrq - subtraction;
      if (temp.b[temp.currNumberOfBursts].cpuTime == 0) {
        temp.currNumberOfBursts++;
        burstFlag = true;
      }
    }
    sprintf(verboseOutput, "At time %d: Thread %d of Process %d moves from running to blocked\n", currentTime, temp.thread, temp.process);
    strcat(realVerbose, verboseOutput);
    if (temp.currNumberOfBursts != temp.numberOfBursts) {
      if (temp.b[temp.currNumberOfBursts - 1].cpuTime == 0 && burstFlag == true) {
        temp.currIOTime += temp.b[temp.currNumberOfBursts - 1].ioTime;
        temp.updatedArrivalTime = currentTime + temp.b[temp.currNumberOfBursts - 1].ioTime;
      } else {
        temp.updatedArrivalTime = currentTime;
      }
      if (pq != NULL) {
        push(&pq, temp);
      } else {
        pq = newThread(temp);
      }
    } else {
      sprintf(verboseOutput, "At time %d: Thread %d of Process %d moves from ready to running\n", currentTime, temp.thread, temp.process);
      strcat(realVerbose, verboseOutput);
      sprintf(detailedOutput, "thread %d of Process %d:\n", temp.thread, temp.process);
      strcat(realDetailed, detailedOutput);
      sprintf(detailedOutput, "\tarrivalTime: %d:\n", temp.arrivalTime);
      strcat(realDetailed, detailedOutput);
      sprintf(detailedOutput,"\tserviceTime: %d, I/OTime: %d, turnaroundTime: %d, finishTime: %d\n", temp.currCPUTime, temp.currIOTime, (currentTime - temp.arrivalTime), currentTime);
      strcat(realDetailed, detailedOutput);
      if ((currentTime - temp.arrivalTime) > processTurnaround[temp.process - 1]) {
        // set turnaround for that process
        processTurnaround[temp.process - 1] = currentTime;
      }
      temp.finishTime = currentTime;
      temp.turnaround = temp.finishTime - temp.arrivalTime;
      temp.updatedArrivalTime = (temp.process * 100) + temp.thread;
      sprintf(verboseOutput, "At time %d: Thread %d of Process %d moves from running to terminated\n", currentTime, temp.thread, temp.process);
      strcat(realVerbose, verboseOutput);
    }
  }
  // first already have total time
  // so now get the average turnaround time of the processes
  printf("Total Time Required = %d\n", currentTime);
  int totalTurnaround = 0;
  for (int i = 0; i < numberOfProcesses; i++) {
    totalTurnaround += processTurnaround[i];
  }
  free(processTurnaround);
  printf("Average Turnaround Time is %.1lf units\n", totalTurnaround / (double)numberOfProcesses);
  // util = total cpu time / total time
  printf("CPU Utilization is %.1lf%%\n", (currentTime - totalSwitch - idleTime) * 100 / ((double)currentTime));
  if (detailed == 1) {
    printf("%s", realDetailed);
  }
  if (verbose == 1) {
    printf("%s", realVerbose);
  }
}

int main(int argc, char **argv) {
  int detailed = 0;
  int verbose = 0;
  int rr = 0;
  int rrq = 0;
  // check for args
  for (int i = 0; i < argc; i++) {
    if (strcmp("-d", argv[i]) == 0) {
      detailed = 1;
    } else if (strcmp("-r", argv[i]) == 0) {
      rr = 1;
    } else if (strcmp("-v", argv[i]) == 0) {
      verbose = 1;
    }
    if (rr == 1 && atoi(argv[i]) != 0) {
      rrq = atoi(argv[i]);
    }
  }
  /*printf("-d: %d, -r: %d, -rrq: %d, -v:%d\n", detailed, rr, rrq, verbose);*/
  if (rr == 0) {
    FCFS(detailed, verbose);
  } else {
    RR(verbose, rrq, detailed);
  }
  return 0;
}
