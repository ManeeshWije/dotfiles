//NAME: MANEESH WIJEWARDHANA
//ID: 1125828
//EMAIL: mkandage@uoguelph.c
#include "memsys.h"
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    int lt;
    int gte;
};

struct Tree
{
    unsigned int width;
    int root;
};

void attachNode(struct memsys *memsys, int *node_ptr, void *src, unsigned int width);

void attachChild(struct memsys *memsys, int *node_ptr, void *src, unsigned int width, int direction);

int comparNode(struct memsys *memsys, int *node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width);

int next(struct memsys *memsys, int *node_ptr, int direction);

void readNode(struct memsys *memsys, int *node_ptr, void *dest, unsigned int width);

void detachNode(struct memsys *memsys, int *node_ptr);

void freeNodes(struct memsys *memsys, int *node_ptr);


struct Tree *newTree(struct memsys *memsys, unsigned int width);

void freeTree(struct memsys *memsys, struct Tree *tree);

void addItem(struct memsys *memsys, struct Tree *tree, int(*compar)(const void *, const void *), void *src);

int searchItem(struct memsys *memsys, struct Tree *tree, int (*compar)(const void *, const void *), void *target);
