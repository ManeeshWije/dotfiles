#include <stdio.h>
#include <stdlib.h>

#ifdef ARRAY		// check if compiler was called with ARRAY defined
#include "array.h"	// ARRAY mode: include array.h
#elif defined LIST	// check if compiler was called with LIST defined
#include "list.h"	// LIST mode: include list.h
#else			// neither mode
#error You must compile this code with either the -DLIST or the -DARRAY option.
#include <stop>		// fail
#endif

/* This program will conduct a bunch of tests on either an array or a list.
 */

#define	CAPACITY	100	// total capacity of the array
#define NEL		 20	// number of elements of the series to include



int main( int argc, char **argv )
{
  int i;
  double number;

  struct memsys *memsys;
  
  memsys = init( 32760, 512 );

  // declare sequence to be the appropriate data type
#ifdef ARRAY
  struct Array *sequence;
#endif
#ifdef LIST
  struct List *sequence;
#endif

  // create the appropriate data type
#ifdef ARRAY
  sequence = newArray( memsys, sizeof( double ), CAPACITY );
#endif
#ifdef LIST
  sequence = newList( memsys, sizeof( double ) );;
#endif


  printf( "after new\n" );
  printops( memsys ); // make sure you are using the latest version of memsys
  printf( "\n\n" );

  // fill data structure with doubles, numbered from 0 to NEL-1
  for (i=0;i<NEL;i++)
  {
    number = i;
    appendItem( memsys, sequence, &number );
  }

  printf( "after appendItem x 20\n" );
  printops( memsys );
  printf( "\n\n" );

  printf( "Initial data:\n" );
  for (i=0;i<NEL;i++)
  {
    readItem( memsys, sequence, i, &number );
    printf( "%d %f\n", i, number );
  }

  printf( "after readItem x 20\n" );
  printops( memsys );
  printf( "\n\n" );

  // now insert the value 7.5 at index 8
  number = 7.5;
  insertItem( memsys, sequence, 8, &number );
  printf( "after insertItem =7.5 at index 8\n" );
  printops( memsys );
  printf( "\n\n" );

  for (i=0;i<NEL+1;i++)
  {
    readItem( memsys, sequence, i, &number );
    printf( "%d %f\n", i, number );
  }

  printf( "after readItem x 21\n" );
  printops( memsys );
  printf( "\n\n" );

  // now prepend the value -1.0
  number = -1.0;
  prependItem( memsys, sequence, &number );
  printf( "after prependItem\n" );
  printops( memsys );
  printf( "\n\n" );


  printf( "After prepend:\n" ); 
  for (i=0;i<NEL+2;i++)
  {
    readItem( memsys, sequence, i, &number );
    printf( "%d %f\n", i, number );
  }

  printf( "after readItem x 22\n" );
  printops( memsys );
  printf( "\n\n" );

  // delete element 16
  deleteItem( memsys, sequence, 16 );
  printf( "after deleteItem\n" );
  printops( memsys );
  printf( "\n\n" );

  printf( "After delete:\n" );
  for (i=0;i<NEL+1;i++)
  {
    readItem( memsys, sequence, i, &number );
    printf( "%d %f\n", i, number );
  }

  printf( "after readItem x 21\n" );
  printops( memsys );
  printf( "\n\n" );

  // free the data structure

#ifdef ARRAY 
  freeArray( memsys, sequence );
#endif

#ifdef LIST
  freeList( memsys, sequence );
#endif

  printf( "after free\n" );
  printops( memsys );
  printf( "\n\n" );

  shutdown( memsys );
}

