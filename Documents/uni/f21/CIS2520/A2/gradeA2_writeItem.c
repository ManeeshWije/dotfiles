#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#define CAPACITY 100
#define STRLEN	16

int main( int argc, char **argv )
{
  struct memsys *memsys;
  struct Array *array;
  char string[STRLEN];

  memsys = init( 4096, 5 );
  array = newArray( memsys, STRLEN, CAPACITY );

  for (int i=1;i<argc;i++)  // loop over the arguments
  {
    writeItem( memsys, array, i-1, argv[i] );
  }

  for (int i=0;i<argc-1;i++)
  {
    readItem( memsys, array, i, string );
    printf( "%d %s, ", i, string );
  }

  freeArray( memsys, array );
  shutdown( memsys );
  return 0;
}
