#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

/* This program will fill an array of strings of size 100 with 
 * a bunch of names from the file "names3.txt".
 * It will then search for a bunch of names using findItem.
 * Each time it will report the number of read, write, malloc and free 
 * calls.  Finally it searches for every name in the table and computes
 * the average number of reads per search.
 */

#define	CAPACITY	100	// total capacity of the array
#define STRLEN		50


void readFile( struct memsys *memsys, struct Array *array )
{
  FILE *fp;
  char name[STRLEN];
  char *retval;

  fp = fopen( "names3.txt", "r" );
  if (!fp)
  {
    fprintf( stderr, "Error: could not open names3.txt\n" );
    exit(-1);
  }

  while (!feof(fp))
  {
    retval = fgets( name, STRLEN, fp );

    if (retval!=NULL)
    {
      name[strlen(name)-1]='\0'; // replace \n with \0
      writeItem( memsys, array, array->nel, &name );
    }
  }

  fclose( fp );
}

int cmp( const void *v1, const void *v2 )
{
  const char *s1, *s2;

  s1 = v1;
  s2 = v2;

  // printf( "cmp(\"%s\",\"%s\")\n", s1, s2 );
  return strcmp(s1,s2);
}

int main( int argc, char **argv )
{
  struct memsys *memsys;
  struct Array *array;
  int i;
  int test;
  char *test_names[6] = { "Aguilar, Herbert",
                         "Dominguez, Keon",
                         "Juarez, Brielle",
			 "Reid, Lilly-May",
			 "Yu, Mahdi",
			 "Kremer, Stefan" };
  char name[STRLEN];

  // load the data into the array
  memsys = init(8192,5);
  array = newArray( memsys, STRLEN, CAPACITY );
  readFile( memsys, array );
  printf( "Read %d records\n", array->nel );

  // run 6 tests and print the results
  for (test=0;test<6;test++)
  {
    i=findItem( memsys, array, &cmp, test_names[test] );
    printf( "%s: i=%d\n", test_names[test], i );

    print( memsys );
    printf( "\n" );
  }

  // find every single item in the array
  for (test=0;test<CAPACITY;test++)
  {
    readItem( memsys, array, test, name );
    i = findItem( memsys, array, &cmp, name );
    printf( "%d %d\n", test, i );
  }


  freeArray( memsys, array );

  print( memsys );
  shutdown( memsys );
}

