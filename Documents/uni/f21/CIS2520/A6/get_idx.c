/* this program returns the index of a string
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main( int argc, char **argv )
{
  char idxname[BUFFER];
  char txtname[BUFFER];

  char *basename;
  char *value;
  long hash_table[ HASHSIZE ];

  if (argc!=3)
  {
    fprintf( stderr, "Usage: %s basename value\n", argv[0] );
    exit(-1);
  }

  // identify text file name
  strcpy( idxname, argv[1] );
  strcat( idxname, ".idx" );
  strcpy( txtname, argv[1] );
  strcat( txtname, ".txt" );

  // basefile for hashing
  basename = argv[1];

  // target value
  value = argv[2];

  // load hashtable from file into memory
  get_hashtable( basename, hash_table );

  // open text file
  FILE *idxfile = fopen( idxname, "r" );
  FILE *txtfile = fopen( txtname, "r" );

  // print result of hash_lookup
  printf( "%ld\n", hash_lookup( value, hash_table, idxfile, txtfile ) );
  fclose( idxfile );
  fclose( txtfile );


  return 0;
} 
