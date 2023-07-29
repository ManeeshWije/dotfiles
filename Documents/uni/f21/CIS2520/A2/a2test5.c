#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

/* This program will fill an array of structures of size 100 with
 * a bunch of names from the file names.txt.  It then tries to exceed
 * the capacity of the array.
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
    fprintf(stderr, "Cannot open names.txt\n");
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

  strcpy(name.first, "Stefan");
  strcpy(name.last, "Kremer");

  writeItem(memsys, array, array->nel, &name);
}

int main(int argc, char **argv) {
  struct Name name;
  struct memsys *memsys;
  struct Array *array;
  int i;

  memsys = init(8192, 5);
  array = newArray(memsys, sizeof(struct Name), CAPACITY);

  readFile(memsys, array);

  printf("Read %d records\n", array->nel);

  for (i = 0; i < array->nel; i++) {
    readItem(memsys, array, i, &name);
    printf("%2d:  %s, %s\n", i, name.last, name.first);
  }

  freeArray(memsys, array);

  print(memsys);
  shutdown(memsys);
}
