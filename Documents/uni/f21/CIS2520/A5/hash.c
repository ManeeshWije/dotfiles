//NAME: Maneesh Wijewardhana
//ID: 1125828
//DATE: 2021/11/03

#include "hash.h"

struct HashTable *createTable(struct memsys *memsys, unsigned int capacity, unsigned int width, int(*hash)(void *, int), int (*compar)(const void*, const void *)) {
    //mallocing for hashtable
    struct HashTable *tempTable = malloc(sizeof(struct HashTable));
    //error checking malloc
    if (tempTable == NULL) {
        fprintf(stderr, "Error malloc\n");
        exit(-1);
    }
    //setting values
    tempTable->capacity = capacity;
    tempTable->width = width;
    tempTable->hash = hash;
    tempTable->compar = compar;
    tempTable->nel = 0;
    tempTable->data = memmalloc(memsys, sizeof(int) * capacity);
    //error checking memallocing
    if (tempTable->data == MEMNULL) {
        fprintf(stderr, "Error memalloc\n");
        exit(-1);
    }
    //setting value of each element in array to MEMNULL?
    int temp = MEMNULL;
    for (int i = 0; i < tempTable->capacity; i++) {
        setval(memsys, &temp, sizeof(int), tempTable->data + (i * sizeof(int)));
    }
    return tempTable;
}   

void addElement(struct memsys *memsys, struct HashTable *table, int addr) {
    //error checking
    if (table->nel == table->capacity) {
        fprintf(stderr, "Error, addElement\n");
        exit(-1);
    }
    //new local variable to send to hash function
    void *temp = malloc(table->width);
    getval(memsys, temp, table->width, addr);

    //index in memsys
    int index = table->hash(temp, table->capacity);
    //holding address in array
    int currAddr;
    int counter = 0;
    //loop at least once
    while(counter < table->capacity) {
        //data starts at table+index
        int newAddr = table->data + (index * sizeof(int));
        getval(memsys, &currAddr, sizeof(int), newAddr);
        //if curraddr is empty, set the value, free and return out of condition
        if(currAddr == MEMNULL) {
            setval(memsys, &addr, sizeof(int), newAddr);
            table->nel++;
            free(temp);
            return;
        }
        //move on to next index
        index++;
        counter++;
        //check to see if need to loop around 
        if(index == table->capacity) {
            index = 0;
        }
    }
    free(temp);
}

int getElement(struct memsys *memsys, struct HashTable *table, void *key) {
    //new local variable to send to hash function
    void *temp = malloc(table->width);
    int index = table->hash(key, table->capacity);

    //holding address in array
    int currAddr;
    int counter = 0;

    //loop at lest once
    while(counter < table->capacity) {
        //data is beginning of table + index
        int newAddr = table->data + (index * sizeof(int)); 
        getval(memsys, &currAddr, sizeof(int), newAddr);
        if(currAddr == MEMNULL) {
            free(temp);
            return MEMNULL;
        }
        getval(memsys, temp, table->width, currAddr);
        //if match
        if(table->compar(temp, key) == 0) {
            free(temp);
            return currAddr;
        }
        //if not, increment and try again
        index++;
        counter++;
        if (index == table->capacity) {
            index = 0;
        }
    }
    free(temp);
    return currAddr;
}

void freeTable(struct memsys *memsys, struct HashTable *table) {
    //freeing hash table in memsys
    memfree(memsys, table->data);
    //freeing table structure
    free(table);
}

int hashAccuracy(struct memsys *memsys, struct HashTable *table) {
    void *temp = malloc(table->width);
    int currAddr;
    int sum = 0;

    for(int i = 0; i < table->capacity; i++) {
        //new address location
        int newAddr = table->data + (sizeof(int) * i);
        getval(memsys, &currAddr, sizeof(int), newAddr);
        //make sure item that we get is not memnull
        if (currAddr != MEMNULL) {
            getval(memsys, temp, table->width, currAddr);
            //hash the value of that index
            int value = table->hash(temp, table->capacity);
            //now check how far from index and compute proper calculations based off of it
            if (i == value) {
                //we dont have to do anything
            }
            else if (i > value) {
                sum += (i - value);
            }
            else {
                sum += (table->capacity - i) + value;
            }
        }
    }
    free(temp);
    return sum;
}
