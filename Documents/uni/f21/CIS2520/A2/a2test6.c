#include <stdio.h>
#include <stdlib.h>
#include "array.h"

/* This program will fill an array of doubles of size 100 with the first 
 * 20 non-negative integers.
 */

#define	CAPACITY	100	// total capacity of the array
#define NEL		 20	// number of elements of the series to include

int main( int argc, char **argv )
{
  int i;
  double number;
  struct Array *array;
  struct memsys *memsys;

  memsys = init( 4096, 5 );
  array = newArray( memsys, sizeof( double ), CAPACITY );

  for (i=0;i<NEL;i++)
  {
    number = i;
    appendItem( memsys, array, &number );
  }

  printf( "Initial array:\n" );
  for (i=0;i<array->nel;i++)
  {
    readItem( memsys, array, i, &number );
    printf( "%d %f\n", i, number );
  }


  number = 7.5;
  insertItem( memsys, array, 8, &number );

  printf( "After insert:\n" );
  for (i=0;i<array->nel;i++)
  {
    readItem( memsys, array, i, &number );
    printf( "%d %f\n", i, number );
  }

  number = -1.0;
  prependItem( memsys, array, &number );
 
  printf( "After prepend:\n" ); 
  for (i=0;i<array->nel;i++)
  {
    readItem( memsys, array, i, &number );
    printf( "%d %f\n", i, number );
  }

  deleteItem( memsys, array, 16 );

  printf( "After delete:\n" );
  for (i=0;i<array->nel;i++)
  {
    readItem( memsys, array, i, &number );
    printf( "%d %f\n", i, number );
  }

  
  freeArray( memsys, array );

  print( memsys );
  shutdown( memsys );
}

