/*
NAME: MANEESH WIJEWARDHANA
ID: 1125828
EMAIL: mkandage@uoguelph.ca
COURSE: CIS*3110
DUE DATE: APRIL 7, 2022

ASSIGNMENT 3 - MEMORY MANAGEMENT
*/
#include "holes.h"
#define MEMORY_SIZE 1024
Process *memoryList;
int memory[MEMORY_SIZE];

int main(int argc, char *argv[]) {
  // read command line arguments
  if(argc != 3){
    printf("Error: Incorrect number of arguments.\n");
    return 1;
  }
  // read string from command line argument
  char *filename = argv[1];
  char *flag = argv[2];

  // check flags and run corresponding function
  if (strcmp(flag, "first") == 0) {
    first(filename, flag);
  } else if (strcmp(flag, "best") == 0) {
    best(filename, flag);
  } else if (strcmp(flag, "worst") == 0) {
    worst(filename, flag);
  } else if (strcmp(flag, "next") == 0) {
    next(filename, flag);
  } else {
    printf("Error: Invalid flag.\n");
    return 1;
  }
}

int addFirst(Process **procHead) {
  if (*procHead == NULL) {
    // no more processes left to add
    return 1;
  }
  bool isHole = true;
  int holeSize = 0;
  int holeStart = 0;
  int index = 0;
  Process *temp;
  // iterate and find holes
  for (int i = 0; i < MEMORY_SIZE; i++) {
    isHole = false;
    holeSize = 0;
    index = i;
    // loop till end of memoery or find a hole
    while (memory[index] == 0 && index < MEMORY_SIZE) {
      isHole = true;
      holeSize++;
      if (holeSize == 1) {
        holeStart = i;
      }
      index++;
    }
    // fill that hole with the process
    if (isHole == true && holeSize >= (*procHead)->size) {
      // remove from queue
      temp = dequeue(procHead);
      // load it into memory array
      for (int j = 0; j < temp->size; j++) {
        memory[holeStart] = temp->id;
        holeStart++;
      }
      // add to memory list
      Process *temp2;
      if (memoryList == NULL) {
        memoryList = temp;
        temp2 = NULL;
      } else {
        temp2 = memoryList;
        while (temp2->next != NULL) {
          temp2 = temp2->next;
        }
        if (temp2->next == NULL) {
          temp2->next = temp;
        }
      }
      // loaded process
      return 0;
    }
  }
  // no hole large enough to fit
  return -1;
}

void swap(Process **procHead) {
  Process *p;
  if (memoryList == NULL) {
    return;
  }
  // create temp
  // remove from memoryList
  Process *temp = memoryList;
  memoryList = memoryList->next;
  temp->next = NULL;
  p = temp;
  // remove from memory array
  int i = 0;
  // loop until memory does not have a process
  for (; memory[i++] != p->id;){
    continue;
  }
  // decrement index
  i--;
  // set that memory to free
  for (; memory[i] == p->id; i++) {
    memory[i] = 0;
  }
  // increment swaps
  p->swaps++;
  // if swaps more than 3, remove from memory list and add to queue
  if (p->swaps < 3) {
    enqueue(p, procHead);
  } else { // free the process and set to null
    p = NULL;
  }
}

void first(char *filename, char *flag) {
  // set all spots to free
  for (int i = 0; i < MEMORY_SIZE; i++) {
    memory[i] = 0;
  }
  // open file
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: File not found.\n");
    return;
  }
  // read file
  char buff[256];
  int i = 0;
  Process *p;
  Process *head = NULL;
  int size;
  int id;
  char *token;
  while (fgets(buff, sizeof(buff), fp)) {
    // remove newline
    buff[strcspn(buff, "\n")] = 0;
    token = strtok(buff, " ");
    while (token != NULL) {
      // parse id and memory chunk
      if (i == 0) {
        id = atoi(token);
      } else if (i == 1) {
        size = atoi(token);
      }
      token = strtok(NULL, " ");
      i++;
    }
    p = createProcess(id, size);
    enqueue(p, &head);
    i = 0;
  }
  // close file
  fclose(fp);
  // print queue to test
  /*printQueue(head);*/
  int isLoaded = 1;
  int numOfLoads = 0;
  float currentUsage = 0;
  float totalUsage = 0;
  float avgProc = 0;
  float avgHoles = 0;

  // start first algo
  isLoaded = addFirst(&head);
  // loop until all processes are loaded
  while (isLoaded != 1) {
    // increment number of loads
    numOfLoads++;
    // loop until no more space
    while (isLoaded == -1) {
      // swap out processes
      swap(&head);
      isLoaded = addFirst(&head);
    }
    // avg num holes calculations
    bool isHole = true;
    int numHoles = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
      if (isHole == true) {
        if (memory[i] == 0) {
          isHole = false;
        }
      } else {
        if (memory[i] != 0) {
          isHole = true;
          numHoles++;
        }
      }
    }
    if (isHole == false) {
      numHoles++;
    }
    avgHoles += numHoles;
    // avg process calculations
    int numProc = 0;
    if (memoryList != NULL) {
      // at least 1 process in memory
      numProc = 1; 
      Process *temp = memoryList;
      while (temp->next != NULL) {
        numProc++;
        temp = temp->next;
      }
    }
    avgProc += numProc;
    // current mem usage calculations
    int memUsed = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
      if (memory[i] != 0) {
        memUsed++;
      }
    }
    currentUsage = (float)memUsed / (float)MEMORY_SIZE * 100;
    totalUsage += currentUsage;
    printf("pid loaded, #processes = %d, #holes = %d, %memusage = %.0f, cumulative %mem = %.0f\n", numProc, numHoles, floorf(currentUsage), floorf(totalUsage/numOfLoads));
    // next iteration
    isLoaded = addFirst(&head);
  }
  // calculate averages
  avgHoles /= numOfLoads;
  avgProc /= numOfLoads;
  // print final
  printf("Total loads = %d, Average #processes = %.1f, Average number of holes = %.1f, Cumulative %mem = %.0f\n", numOfLoads, avgProc, avgHoles, floorf(totalUsage/numOfLoads));
}

int addBest(Process **procHead) {
  if (*procHead == NULL) {
    // no more processes left to add
    return 1;
  }
  bool isHole = true;
  bool isOptimalHole = false;
  int holeSize = 0;
  int holeStart = 0;
  int index = 0;
  int optimalHole = INT_MAX;
  int optimalHoleIndex = 0;
  Process *temp;
  // iterate and find holes
  for (int i = 0; i < MEMORY_SIZE; i++) {
    isHole = false;
    holeSize = 0;
    index = i;
    // loop till end of memoery or find a hole
    while (memory[index] == 0 && index < MEMORY_SIZE) {
      isHole = true;
      holeSize++;
      if (holeSize == 1) {
        holeStart = i;
      }
      index++;
    }
    // fill that hole with the process if smaller hole was found
    // save size and start of that hole
    if (isHole == true && holeSize >= (*procHead)->size && holeSize < optimalHole) {
      isOptimalHole = true;
      optimalHole = holeSize;
      optimalHoleIndex = holeStart;
    }
    // prevents recounting same elements in array
    i = index;
  }
  // load processes
  if (isOptimalHole == true && optimalHole >= (*procHead)->size) {
    // remove from queue
    temp = dequeue(procHead);
    // load it into memory array
    for (int j = 0; j < temp->size; j++) {
      memory[optimalHoleIndex] = temp->id;
      optimalHoleIndex++;
    }
    // add to memory list
    Process *temp2;
    if (memoryList == NULL) {
      memoryList = temp;
      temp2 = NULL;
    } else {
      temp2 = memoryList;
      while (temp2->next != NULL) {
        temp2 = temp2->next;
      }
      if (temp2->next == NULL) {
        temp2->next = temp;
      }
    }
    // loaded process
    return 0;
  }
  // no hole large enough to fit
  return -1;
}

void best(char *filename, char *flag) { 
  // set all spots to free
  for (int i = 0; i < MEMORY_SIZE; i++) {
    memory[i] = 0;
  }
  // open file
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: File not found.\n");
    return;
  }
  // read file
  char buff[256];
  int i = 0;
  Process *p;
  Process *head = NULL;
  int size;
  int id;
  char *token;
  while (fgets(buff, sizeof(buff), fp)) {
    // remove newline
    buff[strcspn(buff, "\n")] = 0;
    token = strtok(buff, " ");
    while (token != NULL) {
      // parse id and memory chunk
      if (i == 0) {
        id = atoi(token);
      } else if (i == 1) {
        size = atoi(token);
      }
      token = strtok(NULL, " ");
      i++;
    }
    p = createProcess(id, size);
    enqueue(p, &head);
    i = 0;
  }
  // close file
  fclose(fp);
  // print queue to test
  /*printQueue(head);*/
  int isLoaded = 1;
  int numOfLoads = 0;
  float currentUsage = 0;
  float totalUsage = 0;
  float avgProc = 0;
  float avgHoles = 0;

  // start best algo
  isLoaded = addBest(&head);
  // loop until all processes are loaded
  while (isLoaded != 1) {
    // increment number of loads
    numOfLoads++;
    // loop until no more space
    while (isLoaded == -1) {
      // swap out processes
      swap(&head);
      isLoaded = addBest(&head);
    }
    // avg num holes calculations
    bool isHole = true;
    int numHoles = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
      if (isHole == true) {
        if (memory[i] == 0) {
          isHole = false;
        }
      } else {
        if (memory[i] != 0) {
          isHole = true;
          numHoles++;
        }
      }
    }
    if (isHole == false) {
      numHoles++;
    }
    avgHoles += numHoles;
    // avg process calculations
    int numProc = 0;
    if (memoryList != NULL) {
      // at least 1 process in memory
      numProc = 1; 
      Process *temp = memoryList;
      while (temp->next != NULL) {
        numProc++;
        temp = temp->next;
      }
    }
    avgProc += numProc;
    // current mem usage calculations
    int memUsed = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
      if (memory[i] != 0) {
        memUsed++;
      }
    }
    currentUsage = (float)memUsed / (float)MEMORY_SIZE * 100;
    totalUsage += currentUsage;
    printf("pid loaded, #processes = %d, #holes = %d, %memusage = %.0f, cumulative %mem = %.0f\n", numProc, numHoles, floorf(currentUsage), floorf(totalUsage/numOfLoads));
    // next iteration
    isLoaded = addBest(&head);
  }
  avgHoles /= numOfLoads;
  avgProc /= numOfLoads;
  printf("Total loads = %d, Average #processes = %.1f, Average number of holes = %.1f, Cumulative %mem = %.0f\n", numOfLoads, avgProc, avgHoles, floorf(totalUsage/numOfLoads));
}

int addNext(Process **procHead) {
  if (*procHead == NULL) {
    // no more processes left to add
    return 1;
  }
  bool isHole = true;
  int holeSize = 0;
  int holeStart = 0;
  int index = 0;
  Process *temp;
  Process *last;
  bool isFirst = false;
  int nextFitStartIndex = 0;
  // get most recent loaded process 
  if (memoryList == NULL) {
  } else {
    Process *temp2 = memoryList;
    while (temp2->next != NULL) {
      temp2 = temp2->next;
    }
    last = temp2;
  }
  if (last != NULL) {
    int end = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
      if (memory[i] == last->id) {
        end = i;
      }
    }
    nextFitStartIndex = end;
  }
  // iterate and find holes
  // loop to the start once end of mem is reached
  for (int i = nextFitStartIndex; isFirst == false || i != nextFitStartIndex; i++) {
    if (i >= MEMORY_SIZE) {
      // set index to start
      i = 0;
      isFirst = true;
    }
    isHole = false;
    holeSize = 0;
    index = i;
    // loop till end of memoery or find a hole
    while (memory[index] == 0 && index < MEMORY_SIZE) {
      isHole = true;
      holeSize++;
      if (holeSize == 1) {
        holeStart = i;
      }
      index++;
    }
    // load processes
    if (isHole == true && holeSize >= (*procHead)->size) {
      // remove from queue
      temp = dequeue(procHead);
      // load it into memory array
      for (int j = 0; j < temp->size; j++) {
        memory[holeStart] = temp->id;
        holeStart++;
      }
      // add to memory list
      Process *temp2;
      if (memoryList == NULL) {
        memoryList = temp;
        temp2 = NULL;
      } else {
        temp2 = memoryList;
        while (temp2->next != NULL) {
          temp2 = temp2->next;
        }
        if (temp2->next == NULL) {
          temp2->next = temp;
        }
      }
      // loaded process
      return 0;
    }
    // prevent recount
    i = index;
  }
  // no hole large enough to fit
  return -1;
}

void next(char *filename, char *flag) {
  // set all spots to free
  for (int i = 0; i < MEMORY_SIZE; i++) {
    memory[i] = 0;
  }
  // open file
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: File not found.\n");
    return;
  }
  // read file
  char buff[256];
  int i = 0;
  Process *p;
  Process *head = NULL;
  int size;
  int id;
  char *token;
  while (fgets(buff, sizeof(buff), fp)) {
    // remove newline
    buff[strcspn(buff, "\n")] = 0;
    token = strtok(buff, " ");
    while (token != NULL) {
      // parse id and memory chunk
      if (i == 0) {
        id = atoi(token);
      } else if (i == 1) {
        size = atoi(token);
      }
      token = strtok(NULL, " ");
      i++;
    }
    p = createProcess(id, size);
    enqueue(p, &head);
    i = 0;
  }
  // close file
  fclose(fp);
  // print queue to test
  /*printQueue(head);*/
  int isLoaded = 1;
  int numOfLoads = 0;
  float currentUsage = 0;
  float totalUsage = 0;
  float avgProc = 0;
  float avgHoles = 0;

  // start next algo
  isLoaded = addNext(&head);
  // loop until all processes are loaded
  while (isLoaded != 1) {
    // increment number of loads
    numOfLoads++;
    // loop until no more space
    while (isLoaded == -1) {
      // swap out processes
      swap(&head);
      isLoaded = addNext(&head);
    }
    // avg num holes calculations
    bool isHole = true;
    int numHoles = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
      if (isHole == true) {
        if (memory[i] == 0) {
          isHole = false;
        }
      } else {
        if (memory[i] != 0) {
          isHole = true;
          numHoles++;
        }
      }
    }
    if (isHole == false) {
      numHoles++;
    }
    avgHoles += numHoles;
    // avg process calculations
    int numProc = 0;
    if (memoryList != NULL) {
      // at least 1 process in memory
      numProc = 1; 
      Process *temp = memoryList;
      while (temp->next != NULL) {
        numProc++;
        temp = temp->next;
      }
    }
    avgProc += numProc;
    // current mem usage calculations
    int memUsed = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
      if (memory[i] != 0) {
        memUsed++;
      }
    }
    currentUsage = (float)memUsed / (float)MEMORY_SIZE * 100;
    totalUsage += currentUsage;
    // print each iteration
    printf("pid loaded, #processes = %d, #holes = %d, %memusage = %.0f, cumulative %mem = %.0f\n", numProc, numHoles, floorf(currentUsage), floorf(totalUsage/numOfLoads));
    // next iteration
    isLoaded = addNext(&head);
  }
  // calculate averages
  avgHoles /= numOfLoads;
  avgProc /= numOfLoads;
  // print final
  printf("Total loads = %d, Average #processes = %.1f, Average number of holes = %.1f, Cumulative %mem = %.0f\n", numOfLoads, avgProc, avgHoles, floorf(totalUsage/numOfLoads));
}

int addWorst(Process **procHead) {
  if (*procHead == NULL) {
    // no more processes left to add
    return 1;
  }
  bool isHole = true;
  int holeSize = 0;
  int holeStart = 0;
  int index = 0;
  int optimalHole = 0;
  int optimalHoleIndex = 0;
  Process *temp;
  // iterate and find holes
  for (int i = 0; i < MEMORY_SIZE; i++) {
    isHole = false;
    holeSize = 0;
    index = i;
    // loop till end of memoery or find a hole
    while (memory[index] == 0 && index < MEMORY_SIZE) {
      isHole = true;
      holeSize++;
      if (holeSize == 1) {
        holeStart = i;
      }
      index++;
    }
    // fill that hole with the process if smaller hole was found
    // save size and start of that hole
    if (isHole == true && holeSize > optimalHole) {
      optimalHole = holeSize;
      optimalHoleIndex = holeStart;
    }
  }
  // load processes
  if (optimalHole >= (*procHead)->size) {
    // remove from queue
    temp = dequeue(procHead);
    // load it into memory array
    for (int j = 0; j < temp->size; j++) {
      memory[optimalHoleIndex] = temp->id;
      optimalHoleIndex++;
    }
    // add to memory list
    Process *temp2;
    if (memoryList == NULL) {
      memoryList = temp;
      temp2 = NULL;
    } else {
      temp2 = memoryList;
      while (temp2->next != NULL) {
        temp2 = temp2->next;
      }
      if (temp2->next == NULL) {
        temp2->next = temp;
      }
    }
    // loaded process
    return 0;
  }
  // no hole large enough to fit
  return -1;
}

void worst(char *filename, char *flag) {
  // set all spots to free
  for (int i = 0; i < MEMORY_SIZE; i++) {
    memory[i] = 0;
  }
  // open file
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error: File not found.\n");
    return;
  }
  // read file
  char buff[256];
  int i = 0;
  Process *p;
  Process *head = NULL;
  int size;
  int id;
  char *token;
  while (fgets(buff, sizeof(buff), fp)) {
    // remove newline
    buff[strcspn(buff, "\n")] = 0;
    token = strtok(buff, " ");
    while (token != NULL) {
      // parse id and memory chunk
      if (i == 0) {
        id = atoi(token);
      } else if (i == 1) {
        size = atoi(token);
      }
      token = strtok(NULL, " ");
      i++;
    }
    p = createProcess(id, size);
    enqueue(p, &head);
    i = 0;
  }
  // close file
  fclose(fp);
  // print queue to test
  /*printQueue(head);*/
  int isLoaded = 1;
  int numOfLoads = 0;
  float currentUsage = 0;
  float totalUsage = 0;
  float avgProc = 0;
  float avgHoles = 0;

  // start worst algo
  isLoaded = addWorst(&head);
  // loop until all processes are loaded
  while (isLoaded != 1) {
    // increment number of loads
    numOfLoads++;
    // loop until no more space
    while (isLoaded == -1) {
      // swap out processes
      swap(&head);
      isLoaded = addWorst(&head);
    }
    // avg num holes calculations
    bool isHole = true;
    int numHoles = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
      if (isHole == true) {
        if (memory[i] == 0) {
          isHole = false;
        }
      } else {
        if (memory[i] != 0) {
          isHole = true;
          numHoles++;
        }
      }
    }
    if (isHole == false) {
      numHoles++;
    }
    avgHoles += numHoles;
    // avg process calculations
    int numProc = 0;
    if (memoryList != NULL) {
      // at least 1 process in memory
      numProc = 1; 
      Process *temp = memoryList;
      while (temp->next != NULL) {
        numProc++;
        temp = temp->next;
      }
    }
    avgProc += numProc;
    // current mem usage calculations
    int memUsed = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
      if (memory[i] != 0) {
        memUsed++;
      }
    }
    currentUsage = (float)memUsed / (float)MEMORY_SIZE * 100;
    totalUsage += currentUsage;
    // print each iteration
    printf("pid loaded, #processes = %d, #holes = %d, %memusage = %.0f, cumulative %mem = %.0f\n", numProc, numHoles, floorf(currentUsage), floorf(totalUsage/numOfLoads));
    // next iteration
    isLoaded = addWorst(&head);
  }
  // calculate averages
  avgHoles /= numOfLoads;
  avgProc /= numOfLoads;
  // print final
  printf("Total loads = %d, Average #processes = %.1f, Average number of holes = %.1f, Cumulative %mem = %.0f\n", numOfLoads, avgProc, avgHoles, floorf(totalUsage/numOfLoads));
}

