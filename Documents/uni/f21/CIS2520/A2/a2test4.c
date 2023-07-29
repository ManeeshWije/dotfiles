#include "array.h"
#include <stdio.h>
#include <stdlib.h>

/* This program will fill an array of structures of size 100 with
 * a bunch of names from the file "names.txt".
 * It will then write the name to the file "names2.txt", as lastname,
 * firstname; then it will remove the last item using "contract",
 * and finally report the number of read, write, malloc and free
 * calls.
 */

#define CAPACITY 100 // total capacity of the array

struct Name {
  char first[25];
  char last[25];
};

void readFile(struct memsys *memsys, struct Array *array) {
  FILE *fp;
  char buffer[81];
  struct Name name;
  int retval;

  fp = fopen("names.txt", "r");
  if (!fp) {
    fprintf(stderr, "Missing names.txt\n");
    exit(-1);
  }

  // skip the first line
  fgets(buffer, 80, fp);

  while (!feof(fp)) {
    // this scanf call is unsafe if inputs are wider the first or last strings
    retval = fscanf(fp, "%s %s", name.first, name.last);

    if (retval == 2) {
      writeItem(memsys, array, array->nel, &name);
    }
  }

  fclose(fp);
}

int main(int argc, char **argv) {
  struct Name name;
  struct Array *array;
  int i;
  FILE *fp;
  struct memsys *memsys;

  memsys = init(8192, 5);
  array = newArray(memsys, sizeof(struct Name), CAPACITY);

  readFile(memsys, array);

  printf("Read %d records\n", array->nel);

  fp = fopen("names2.txt", "w");
  for (i = 0; i < array->nel; i++) {
    readItem(memsys, array, i, &name);
    fprintf(fp, "%s, %s\n", name.last, name.first);
  }
  fclose(fp);

  contract(memsys, array);
  printf("After contraction:\n");

  for (i = 0; i < array->nel; i++) {
    readItem(memsys, array, i, &name);
    printf("%2d:  %s, %s\n", i, name.last, name.first);
  }

  freeArray(memsys, array);

  print(memsys);
  shutdown(memsys);
}
