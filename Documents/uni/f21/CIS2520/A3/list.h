//NAME: MANEESH WIJEWARDHANA
//ID: 1125828
//EMAIL: mkandage@uoguelph.ca

#include "memsys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  int data;
  int next;
};

struct List {
  unsigned int width;
  int head;
};

void push(struct memsys *memsys, int *node_ptr, void *src, size_t width);

void insert(struct memsys *memsys, int *node_ptr, void *src, size_t width);

void delete (struct memsys *memsys, int *node_ptr);

void readHead(struct memsys *memsys, int *node_ptr, void *dest,
              unsigned int width);

void pop(struct memsys *memsys, int *node_ptr);

int next(struct memsys *memsys, int *node_ptr);

int isNull(struct memsys *memsys, int *node_ptr);

struct List *newList(struct memsys *memsys, unsigned int width);

void freeList(struct memsys *memsys, struct List *list);

int isEmpty(struct memsys *memsys, struct List *list);

void readItem(struct memsys *memsys, struct List *list, unsigned int index,
              void *dest);

void appendItem(struct memsys *memsys, struct List *list, void *src);

void insertItem(struct memsys *memsys, struct List *list, unsigned int index,
                void *src);

void prependItem(struct memsys *memsys, struct List *list, void *src);

void deleteItem(struct memsys *memsys, struct List *list, unsigned int index);

int findItem(struct memsys *memsys, struct List *list,
             int (*compar)(const void *, const void *), void *target);
