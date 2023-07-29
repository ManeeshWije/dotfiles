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
  freeArray( memsys, array );
  printf( "%d ", memsys->mallocs );
  printf( "%d ", memsys->table[0].len );
  printf( "%d", memsys->table[0].used );
  shutdown( memsys );
  return 0;
}
