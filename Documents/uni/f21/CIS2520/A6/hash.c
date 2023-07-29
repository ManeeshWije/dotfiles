#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"



int char2int( unsigned char c )
  /* convert a character into an integer from 1 to 27 */
{
  if ( isupper(c) )
  {
    return (int)(c-'A'+1); // A=1, B=2, C=3, ...
  }
  if ( islower(c) )
  {
    return (int)(c-'a'+1); // a=1, b=2, c=3, ...
  }
  if ( isdigit(c) )
  {
    return 26+(c-'0');
  }
  return  37;
}


long str2int( char *s, int max )
{
  char *c;

  unsigned long number, column, new;

  // convert string to base 28 number
  number = 0;
  column=1;

  for (c=s;(*c);c++)
  {
    number += char2int(*c) * column;
    column *= 38;
  }

  // convert number to a base max number and add up column values
  new = 0;
  while (number)
  {
    new = (new + (number % max)) % max;
    number = number / max;
  }

  return (long)new;

}

void init_hash_table( long hash_table[ HASHSIZE ] )
{
  for (int i=0;i<HASHSIZE;i++)
  {
    hash_table[i] = -1;
  }
}

int add_hash( long hash_table[ HASHSIZE ], int hash_idx, long file_pos )
  /* add the value file_pos (which is a location in the txt file) to
   * the hash table at an empty position closest to hash_idx 
   * it will return the actual index where the file_pos was stored
   */
{
  for (int i=hash_idx;i<HASHSIZE;i++)
  {
    if (hash_table[i]==-1)
    {
      hash_table[i] = file_pos;
      return i;
    }
  }

  for (int i=0;i<hash_idx;i++)
  {
    if (hash_table[i]==-1)
    {
      hash_table[i] = file_pos;
      return i;
    }
  }
  return -1;

}



long hash_lookup( char *key, long hash_table[ HASHSIZE ], FILE *idxfile, FILE *txtfile )
{
  long seekval;
  long hash_idx = str2int( key, HASHSIZE );
  char buffer[BUFFER];

  for (int i=hash_idx;i<HASHSIZE;i++)
  {
    fseek( idxfile, hash_table[i]*sizeof(long), SEEK_SET );
    fread( &seekval, sizeof(long), 1, idxfile );
    fseek( txtfile, seekval, SEEK_SET );
    fgets( buffer, BUFFER, txtfile );
    buffer[ strlen(buffer)-1 ] = '\0';
    if ( strcmp(buffer,key)==0 )
      return hash_table[i];
  }
  for (int i=0;i<hash_idx;i++)
  {
    fseek( idxfile, hash_table[i]*sizeof(long), SEEK_SET );
    fread( &seekval, sizeof(long), 1, idxfile );
    fseek( txtfile, seekval, SEEK_SET );
    fgets( buffer, BUFFER, txtfile );
    buffer[ strlen(buffer)-1 ] = '\0';
    if ( strcmp(buffer,key)==0 )
      return hash_table[i];
  }
  return -1;
}
     

void mk_hashfile( char *basename, long hash_table[ HASHSIZE ] )
{
  char hashfile[BUFFER];
  strcpy( hashfile, basename );
  strcat( hashfile, ".hash" );

  FILE *fphash;

  fphash = fopen( hashfile, "wb" );

  fwrite( hash_table, sizeof(long), HASHSIZE, fphash );

  fclose(fphash);
}

void get_hashtable( char *basename, long hash_table[ HASHSIZE ] )
{
  char hashfile[BUFFER];
  strcpy( hashfile, basename );
  strcat( hashfile, ".hash" );

  FILE *fphash;

  fphash = fopen( hashfile, "rb" );

  fread( hash_table, sizeof(long), HASHSIZE, fphash );

  fclose(fphash);
}

long get_idx( char *string, long hash_table[ HASHSIZE ] )
{
  long hash_idx = str2int( string, HASHSIZE );
  return hash_table[ hash_idx ];
}

