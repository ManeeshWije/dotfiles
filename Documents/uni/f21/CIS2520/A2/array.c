// Name: Maneesh Wijewardhana
// ID: 1125828
// Date: 05-10-2021

#include "array.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Array *newArray(struct memsys *memsys, unsigned int width,
                       unsigned int capacity) {
  struct Array *array = malloc(sizeof(struct Array));
  // setting values
  array->width = width;
  array->capacity = capacity;
  array->nel = 0;
  // using memmalloc to set data
  array->data = memmalloc(memsys, width * capacity);
  if (array->data == MEMNULL) {
    fprintf(stderr, ("Error Memmalloc\n"));
    exit(-1);
  }
  return array;
}

void readItem(struct memsys *memsys, struct Array *array, unsigned int index,
              void *dest) {
  if (index >= array->nel) {
    fprintf(stderr, "Error readItem\n");
    exit(-1);
    // offset so we need to add array->width * index to array->data
  } else {
    getval(memsys, dest, array->width, array->width * index + array->data);
  }
}

void writeItem(struct memsys *memsys, struct Array *array, unsigned int index,
               void *src) {
  if (index > array->nel || index >= array->capacity) {
    fprintf(stderr, "Error writeItem\n");
    exit(-1);
  } else {
    setval(memsys, src, array->width, array->width * index + array->data);
  }
  if (index == array->nel) {
    array->nel++;
  }
}

void contract(struct memsys *memsys, struct Array *array) {
  if (array->nel == 0) {
    fprintf(stderr, "Error contract\n");
    exit(-1);
  } else {
    array->nel--;
  }
}

// freeing all memory as well as malloc'd struct from first func
void freeArray(struct memsys *memsys, struct Array *array) {
  memfree(memsys, array->data);
  free(array);
}

// appends item to end of array
void appendItem(struct memsys *memsys, struct Array *array, void *src) {
  writeItem(memsys, array, array->nel, src);
}

void insertItem(struct memsys *memsys, struct Array *array, unsigned int index,
                void *src) {
  // need to create temp var so we do not edit src
  void *temp = malloc(sizeof(void*)); 
  // starting from elements until i is greater than index we increment down
  for (int i = array->nel; i > index; i--) {
    readItem(memsys, array, i - 1, &temp);
    writeItem(memsys, array, i, &temp);
  }
  free(temp);
  writeItem(memsys, array, index, src);
}

// inserting item into first position
void prependItem(struct memsys *memsys, struct Array *array, void *src) {
  insertItem(memsys, array, 0, src);
}

void deleteItem(struct memsys *memsys, struct Array *array,
                unsigned int index) {
  void *temp = NULL;
  // starting from index up to last element in array
  for (int i = index; i < array->nel - 1; i++) {
    readItem(memsys, array, i + 1, &temp);
    writeItem(memsys, array, i, &temp);
  }
  contract(memsys, array);
}

int findItem(struct memsys *memsys, struct Array *array,
             int (*compar)(const void *, const void *), void *target) {
  void *temp = malloc(sizeof(void *));
  for (int i = 0; i < array->nel; i++) {
    readItem(memsys, array, i, temp);
    if (compar(temp, target) == 0) {
      free(temp);
      return i;
    }
  }
  free(temp);
  return -1;
}

int searchItem(struct memsys *memsys, struct Array *array,
               int (*compar)(const void *, const void *), void *target) {
  void *temp = malloc(sizeof(void *));
  // lowest element
  int low = 0;
  // highest element
  int high = array->nel - 1;
  while (low <= high) {
    // middle element rounded down
    int mid = low + (high - low) / 2;
    readItem(memsys, array, mid, temp);
    // if element was in middle
    if (compar(target, temp) == 0) {
      free(temp);
      return mid;
    }
    // if element is greater, move to right half
    if (compar(temp, target) < 0) {
      low = mid + 1;
    } else { // move to left half
      high = mid - 1;
    }
  }
  free(temp);
  return -1;
}
