#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main( int argc, char **argv )
{
  char *basename;
  int idx, idx2;

  if (argc!=3)
  {
    fprintf( stderr, "Usage: %s basename value\n", argv[0] );
    exit(-1);
  }

  basename = argv[1];
  idx = atoi(argv[2]);

  char txtfile[BUFFER];
  char idxfile[BUFFER];
  char buffer[BUFFER];

  FILE *fptxt, *fpidx;

  strcpy( txtfile, basename );
  strcat( txtfile, ".txt" );

  strcpy( idxfile, basename );
  strcat( idxfile, ".idx" );

  fptxt = fopen( txtfile, "r" );
  fpidx = fopen( idxfile, "r" );

  fseek( fpidx, sizeof(long)*idx, SEEK_SET );
  
  if ( fread( &idx2, sizeof(long), 1, fpidx ) != 1 )
  {
    fprintf( stderr, "Error: invalid index\n" );
    exit(-1);
  }

  fclose( fpidx );

  fseek( fptxt, idx2, SEEK_SET );
  fgets( buffer, BUFFER, fptxt );

  printf( "%s\n", buffer );
  fclose( fptxt );

  return 0;
} 
