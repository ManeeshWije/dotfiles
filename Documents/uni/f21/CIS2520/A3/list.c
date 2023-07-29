// NAME: MANEESH WIJEWARDHANA
// ID: 1125828
// EMAIL: mkandage@uoguelph.ca

#include "list.h"
#include "memsys.h"
#include <stdlib.h>

void push(struct memsys *memsys, int *node_ptr, void *src, size_t width) {
  struct Node tempNode; // declaring a temporary node
  tempNode.data =
      memmalloc(memsys, width); // allocating width bytes of memory to data
  setval(memsys, src, width, tempNode.data); // setting node data to src
  tempNode.next = *node_ptr;                 // setting next node to node_ptr
  *node_ptr = memmalloc(
      memsys,
      sizeof(struct Node)); // allocating size of struct Node to node_ptr
  setval(memsys, &tempNode, sizeof(struct Node),
         *node_ptr); // recording the address of tempnode pointed to by node_ptr
}

void insert(struct memsys *memsys, int *node_ptr, void *src, size_t width) {
  // need two temp nodes to perform insert
  struct Node newNode;
  struct Node tempNode;
  getval(memsys, &tempNode, sizeof(struct Node),
         *node_ptr); // retrieving address in node_ptr into tempnode
  newNode.data = memmalloc(
      memsys, width); // allocating width bytes of data to new nodes data
  setval(memsys, src, width, newNode.data); // setting new nodes data to src
  newNode.next = tempNode.next; // assigning new nodes next to temp nodes next
  tempNode.next =
      memmalloc(memsys, sizeof(struct Node)); // allocating struct Node size
                                              // bytes into tempnodes next
  setval(memsys, &newNode, sizeof(struct Node),
         tempNode.next); // copying structures data into memsys
  setval(
      memsys, &tempNode, sizeof(struct Node),
      *node_ptr); // writing original node back to memsys at original location
}

void delete (struct memsys *memsys, int *node_ptr) {
  // need two temp nodes to perform a delete
  struct Node prevTemp;
  struct Node nextTemp;
  getval(memsys, &prevTemp, sizeof(struct Node),
         *node_ptr); // retrieving node stored in node_ptr
  getval(memsys, &nextTemp, sizeof(struct Node),
         prevTemp.next); // finding next node
  int tempHold = prevTemp.next;
  prevTemp.next = nextTemp.next;  // deleting node
  memfree(memsys, nextTemp.data); // freeing data from node
  memfree(memsys, tempHold);      // freeing whole struct Node
  setval(memsys, &prevTemp, sizeof(struct Node),
         *node_ptr); // setting node_ptr to address of previous node
}

void readHead(struct memsys *memsys, int *node_ptr, void *dest,
              unsigned int width) {
  // error checking for empty list
  if (*node_ptr == MEMNULL) {
    fprintf(stderr, "error, list is empty(readHead)\n");
    exit(-1);
  }
  struct Node tempNode;
  getval(memsys, &tempNode, sizeof(struct Node),
         *node_ptr); // copying width bytes of data from nodeptr into temp
  getval(memsys, dest, width, tempNode.data); // copying data into dest
}

void pop(struct memsys *memsys, int *node_ptr) {
  // error checking for empty list
  if (*node_ptr == MEMNULL) {
    fprintf(stderr, "error, list is empty(pop)");
    exit(-1);
  } else {
    struct Node tempNode;
    getval(memsys, &tempNode, sizeof(struct Node),
           *node_ptr); // retrieving address of node_ptr and putting it into
                       // tempnode
    int tempHold = *node_ptr;
    *node_ptr =
        tempNode.next; // updating address pointed to by node_ptr to next node
    memfree(memsys, tempNode.data); // freeing memory in node data
    memfree(memsys, tempHold);      // freeing whole struct
  }
}

int next(struct memsys *memsys, int *node_ptr) {
  struct Node tempNode;
  // error checking for empty list
  if (*node_ptr == MEMNULL) {
    fprintf(stderr, "error, list is empty(next)\n");
    exit(-1);
  }
  getval(memsys, &tempNode, sizeof(struct Node),
         *node_ptr); // retrieving address of node_ptr and storing in temp node
  return tempNode.next; // returning next temp node
}

int isNull(struct memsys *memsys, int *node_ptr) {
  // if list is empty, return 1, else 0
  if (*node_ptr == MEMNULL) {
    return 1;
  }
  return 0;
}

struct List *newList(struct memsys *memsys, unsigned int width) {
  struct List *list = malloc(sizeof(struct List)); // need to malloc memory
  // error checking for empty list
  if (list == NULL) {
    fprintf(stderr, "error malloc in newList\n");
    exit(-1);
  }
  // assigning values
  list->head = MEMNULL;
  list->width = width;
  return list;
}

void freeList(struct memsys *memsys, struct List *list) {
  while (list->head != MEMNULL) {
    pop(memsys, &list->head); // this frees each element until head is -1
  }
  free(list); // freeing malloced list in newList
}

int isEmpty(struct memsys *memsys, struct List *list) {
  // if list is empty return 1, else 0
  if (list->head == MEMNULL) {
    return 1;
  }
  return 0;
}

// for most item functons, we will use a temp to store list->head and a holder
// variable since we want the node before the memnull node
void readItem(struct memsys *memsys, struct List *list, unsigned int index,
              void *dest) {
  int temp = list->head;
  for (int i = 0; i < index; i++) {
    temp = next(memsys, &temp);
  }
  readHead(memsys, &temp, dest, list->width);
}

void appendItem(struct memsys *memsys, struct List *list, void *src) {
  int tempHold;
  int temp = list->head;
  if (isEmpty(memsys, list) == 1) {
    push(memsys, &list->head, src,
         list->width); // if list is empty, push element into list
  } else {
    while (!(isNull(memsys, &temp))) { // loop through list until not null
      tempHold = temp; // getting value before temp since its null after loop
      temp = next(memsys, &temp);
    }
    insert(memsys, &tempHold, src, list->width); // inserting at end of list
  }
}

void insertItem(struct memsys *memsys, struct List *list, unsigned int index,
                void *src) {
  int tempHold;
  int temp = list->head;
  if (index == 0) {
    push(memsys, &list->head, src,
         list->width); // if index to be inserted into is 0, push element
  } else {
    for (int i = 0; i < index; i++) {
      tempHold = temp;
      temp = next(memsys, &temp); // otherwise, loop thru list until index
    }
    insert(memsys, &tempHold, src,
           list->width); // insert element at given index
  }
}

void prependItem(struct memsys *memsys, struct List *list, void *src) {
  // could either use insertitem at [0] or just push element which prepends
  /*push(memsys, &list->head, src, list->width);*/
  insertItem(memsys, list, 0, src);
}

void deleteItem(struct memsys *memsys, struct List *list, unsigned int index) {
  int temp = list->head;
  int tempHold;
  if (index == 0) {
    pop(memsys, &list->head); // if deleting 0th node, just pop
  } else {
    for (int i = 0; i < index; i++) {
      tempHold = temp;
      temp = next(memsys, &temp); // loop through entire list until given index
    }
    delete (memsys, &tempHold); // delete element at index
  }
}

int findItem(struct memsys *memsys, struct List *list,
             int (*compar)(const void *, const void *), void *target) {
  void *temp = malloc(sizeof(list->width)); // mallocing width bytes into temp
  int tempHead =
      list->head; // temp head since we dont want to work with list->head itself
  int i = 0;
  readHead(memsys, &tempHead, temp,
           list->width); // if first element, then compare
  if (compar(target, temp) == 0) {
    free(temp);
    return i;
  }
  // loop until null head readitem at each index
  // use compar and if == 0, returning index
  while (tempHead != MEMNULL) {
    i++;
    tempHead = next(memsys, &tempHead);
    readItem(memsys, list, i, temp);
    if (compar(temp, target) == 0) {
      free(temp);
      return i;
    }
  }
  free(temp);
  return -1;
}
