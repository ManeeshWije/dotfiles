//NAME: MANEESH WIJEWARDHANA
//ID: 1125828
//EMAIL: mkandage@uoguelph.ca
#include "tree.h"
#include "memsys.h"
#include <stdio.h>
#include <stdlib.h>

void attachNode(struct memsys *memsys, int *node_ptr, void *src, unsigned int width) {
    struct Node tempNode;                               //initializing new tempNode variable
    *node_ptr = memmalloc(memsys, sizeof(struct Node)); //memallocing width bytes of data on node iteself
    tempNode.data = memmalloc(memsys, width);           //memallocing width bytes of data into data portion of Node
    if (tempNode.data == MEMNULL) {
        fprintf(stderr, "Error, memmalloc failed (attachNode)\n"); //error checking
        exit(-1);
    }
    if (*node_ptr == MEMNULL) {
        fprintf(stderr, "Error, memalloc failed (attachNode)\n");
        exit(-1);
    }
    setval(memsys, src, width, tempNode.data); //copying with bytes of data from src to data portion of Node
    tempNode.lt = MEMNULL;                     //setting lower and higher addresses of struct to MEMNULL
    tempNode.gte = MEMNULL;
    setval(memsys, &tempNode, sizeof(struct Node), *node_ptr); //copying address of new structure to the int pointed to by node_ptr
}

void attachChild(struct memsys *memsys, int *node_ptr, void *src, unsigned int width, int direction) {
    struct Node tempNode;                                      //declaring temp node
    getval(memsys, &tempNode, sizeof(struct Node), *node_ptr); //retrieving node stored at address pointed to by node_ptr
    if (direction < 0) {
        attachNode(memsys, &tempNode.lt, src, width); //creating new node and updating lt variable on original node
    }
    else if (direction >= 0) {
        attachNode(memsys, &tempNode.gte, src, width); //creating new node and updating gte variable in original node
    }
    setval(memsys, &tempNode, sizeof(struct Node), *node_ptr); //updating original node in memsys
}

int comparNode(struct memsys *memsys, int *node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width) {
    struct Node tempNode; 
    int *temp = malloc(width); //need temp void to compare target to
    getval(memsys, &tempNode, sizeof(struct Node), *node_ptr); //getting value of node_ptr and storing it in temp address
    getval(memsys, temp, width, tempNode.data); //updating void temp value to the data value of tempnode
    int value = compar(target, temp); //getting return value of comparison
    free(temp); //freeing void temp
    return value; //returning comparison value
}

int next(struct memsys *memsys, int *node_ptr, int direction) {
    struct Node tempNode; //need temp node to retrieve next
    getval(memsys, &tempNode, sizeof(struct Node), *node_ptr);
    if (direction < 0) { //if direction less than 0, getting node whos address is pointed to by node_ptr and returning address of lt
        return tempNode.lt;
    }
    else { //if direction greater than or equal to 0, getting node whos address is pointed to by node_ptr and returning address of gte
        return tempNode.gte;
    }
}

void readNode(struct memsys *memsys, int *node_ptr, void *dest, unsigned int width) {
    if (*node_ptr == MEMNULL) { //error checking if node_ptr is empty
        fprintf(stderr, "Error, node_ptr is empty (readNode)");
        exit(-1);
    }
    else {
        //first getval copies bytes from node whos address is pointed to by node_ptr
        //second getval copies the data variable of tempNode into dest
        struct Node tempNode;
        getval(memsys, &tempNode, sizeof(struct Node), *node_ptr);
        getval(memsys, dest, width, tempNode.data);
    }
}

void detachNode(struct memsys *memsys, int *node_ptr) {
    if (*node_ptr == MEMNULL) { //checking if node is empty
        fprintf(stderr, "Error, node_ptr is empty (detachNode)");
        exit(-1);
    }
    else {
        struct Node tempNode;
        getval(memsys, &tempNode, sizeof(struct Node), *node_ptr); //getting value of node_ptr and storing it in temp address
        int tempHold = *node_ptr; //need to hold value of node_ptr since it will get lost in the next step
        *node_ptr = MEMNULL; //MEMNULL'ing node_ptr
        memfree(memsys, tempNode.data); //freeing data
        memfree(memsys, tempHold); //freeing held value from node_ptr
    }
}

void freeNodes(struct memsys *memsys, int *node_ptr) {
    if (*node_ptr == MEMNULL) {
        return;
    }
    int tempHold = *node_ptr;
    int node1 = next(memsys, &tempHold, -1); //going in the left direction
    int node2 = next(memsys, &tempHold, 1); //going in the right directioon
    freeNodes(memsys, &node1); //freeing left side
    freeNodes(memsys, &node2); //freeing right side
    detachNode(memsys, node_ptr); //deleting original 
}
struct Tree *newTree(struct memsys *memsys, unsigned int width) {
    struct Tree *tree = malloc(sizeof(struct Tree));
    if (tree == NULL) { //if malloc fails
        fprintf(stderr, "error malloc (newTree)\n");
        exit(-1);
    } //setting values for width and root
    tree->width = width;
    tree->root = MEMNULL;
    return tree; //returing pointer to structure
}

void freeTree(struct memsys *memsys, struct Tree *tree) {
    freeNodes(memsys, &tree->root); //freeing root of tree
    free(tree); //freeing tree structure itself
}

void addItem(struct memsys *memsys, struct Tree *tree, int (*compar)(const void *, const void *), void *src) {
    if (tree->root == MEMNULL) {
        attachNode(memsys, &tree->root, src, tree->width);
    } 
    else {
        int temp = tree->root;
        int tempHold;
        int direction;
        while (temp != MEMNULL) {
            tempHold = temp;
            direction = comparNode(memsys, &temp, compar, src, tree->width);
            temp = next(memsys, &temp, direction);
        }
        attachChild(memsys, &tempHold, src, tree->width, direction);
    }
}

int searchItem(struct memsys *memsys, struct Tree *tree, int (*compar)(const void *, const void *), void *target) {
    void *temp = malloc(sizeof(void*));
    struct Node tempNode;
    int tempRoot = tree->root;
    while(tempRoot != MEMNULL){
        int tempHold = tempRoot;
        readNode(memsys, &tempHold, temp, sizeof(struct Node)); //reading each node in tree
        int direction = comparNode(memsys, &tempHold, compar, target, tree->width); //getting return value from comparnode to use for out comparison
        if (direction == 0){ // 0 means a match
            getval(memsys, &tempNode, sizeof(struct Node), tempHold); //getting value from held temp and storing it in tempnode
            getval(memsys, target, tree->width, tempNode.data); //copying data into target to replace original search item
            free(temp);
            return 1;
        } 
        tempRoot = next(memsys, &tempRoot, direction); // traversing list until MEMNULL where loop will stop
    }
    free(temp); //if no match then free and return 0
    return 0; 
}
