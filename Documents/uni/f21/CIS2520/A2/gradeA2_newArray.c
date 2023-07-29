#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#define CAPACITY 100
int main( int argc, char **argv )
{
  struct memsys *memsys;
  struct Array *array;

  memsys = init( 512, 5 );
  printf( "%d ", memsys->mallocs );
  array = newArray( memsys, sizeof(int), CAPACITY );
  printf( "%d ", memsys->mallocs );
  shutdown( memsys );
  return 0;
}
