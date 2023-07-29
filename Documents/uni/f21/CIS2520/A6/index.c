/*
 * This program builds index and hash files based on txt files.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "hash.h"

// global constant for the files
#define FILE_NO 10
char *files[FILE_NO] = { "building", "code", "courseno", "days", "format", "from", "names", "room", "subject", "to" };


void mkindex( char *basename )
  /* create idx and hash files for the given txt file
   */
{
  char txtfile[BUFFER];	// text file name
  char idxfile[BUFFER]; // index file name
  char buffer[BUFFER];  // buffer for gets

  long hash_table[ HASHSIZE ];

  FILE *fptxt, *fpidx;

  long idx, hashidx;
  int i;

  init_hash_table( hash_table );	// initialize empty hash table

  strcpy( txtfile, basename );		// create text file name
  strcat( txtfile, ".txt" );

  strcpy( idxfile, basename );		// create index file name
  strcat( idxfile, ".idx" );

  fptxt = fopen( txtfile, "r" );	// open both files
  fpidx = fopen( idxfile, "wb" );

  // for each line in the text file
  for ( i=0, idx=ftell(fptxt); fgets( buffer, BUFFER, fptxt ); i++, idx=ftell(fptxt) )
  {
    buffer[ strlen(buffer)-1 ] = '\0';	// remove \n
    hashidx = str2int( buffer, HASHSIZE );	// compute its hash index
    hashidx = add_hash( hash_table, hashidx, i );
    fwrite( &idx, sizeof(long), 1, fpidx );
  }

  fclose( fptxt );
  fclose( fpidx );

  mk_hashfile( basename, hash_table );
}


int main( int argc, char **argv )
{

  for (int i=0;i<FILE_NO;i++)
  {
    mkindex( files[i] );
  }

  printf( "%lu\n", sizeof(long) );
  return 0;
}

