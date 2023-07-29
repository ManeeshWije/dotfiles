/*
 * print out the context of a binary file consisting of long integers
 */

#include <stdio.h>

int main( int argc, char **argv )
{
  long val;
  FILE *fp = fopen( argv[1], "rb" );

  for (int i=0; fread( &val, sizeof( long ), 1, fp )==1; i++ )
  {
    if (val>=0)
    {
      printf( "[%05d]: %4ld\n", i, val );
    }
  }

  return 0;
}
