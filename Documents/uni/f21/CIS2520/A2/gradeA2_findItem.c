#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#define CAPACITY 10000	// full version

int cmp( const void *v1, const void *v2 )
{
  const int *i1, *i2;

  i1 = v1;
  i2 = v2;

  // printf( "%d vs %d\n", *i1, *i2 );
  return (*i1 - *i2);
}


int main( int argc, char **argv )
{
  struct memsys *memsys;
  struct Array *array;
  int number;
  int index;
  int numbers[CAPACITY];

  memsys = init( 4096*4096, 5 );
  array = newArray( memsys, sizeof(int), CAPACITY );

  // create a regular array of random integers
  srand( 123 );
  for (int i=0;i<CAPACITY;i++)  // loop over the arguments
  {
    numbers[i] = rand();
  }

  // sort it
  qsort(numbers,CAPACITY,sizeof(int),cmp);

  // transfer the integers into memsys array
  for (int i=0;i<CAPACITY;i++)  // loop over the arguments
  {
    writeItem( memsys, array, i, numbers+i );
  }


  if (strcmp(argv[1],"present")==0)
  {
    number = 917202713;
    index = findItem( memsys, array, cmp, &number );
    printf( "%d %d", index==4242, (memsys->memctr.get>4000 && memsys->memctr.get<6000) );
  }
  else
  {
    number = 917202714;
    index = findItem( memsys, array, cmp, &number );
    printf( "%d %d", index==-1, (memsys->memctr.get>9900 && memsys->memctr.get< 10100 ) );
  }
  
  freeArray( memsys, array );
  shutdown( memsys );
  return 0;
}
