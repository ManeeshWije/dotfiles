#include "tree.h"
#include "memsys.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 128

// create some records to hold peoples names and their phone numbers
struct record
{
  char last_name[STRLEN];
  char first_name[STRLEN];
  char phone_number[13];
};


// function that compares records base (only) on first name
int comp_first_name( const void *ptr1, const void *ptr2 )
{
  const struct record *rec1, *rec2;
  int result;

  rec1 = ptr1;
  rec2 = ptr2;

  result = strcmp( rec1->first_name, rec2->first_name );

#ifdef DEBUG
  printf( "strcmp( \"%s\", \"%s\" )=%d\n", 
          rec1->first_name, rec2->first_name, result );
#endif
  return result;
}

// function that compares records base (only) on last name
int comp_last_name( const void *ptr1, const void *ptr2 )
{
  const struct record *rec1, *rec2;
  int result;

  rec1 = ptr1;
  rec2 = ptr2;

  result = strcmp( rec1->last_name, rec2->last_name );
#ifdef DEBUG
  printf( "strcmp( \"%s\", \"%s\" )=%d\n", 
          rec1->last_name, rec2->last_name, result );
#endif
  return result;
}

int main( int argc, char **argv )
{
  FILE *fp;
  int result;
  char buffer[256];

  struct record record;
  struct Tree *by_last_name;
  struct Tree *by_first_name;

  struct memsys *memsys;

  // initialize memsys with lots of ram and allocations 
  memsys = init(262144,512);

  // create two binary trees storing records, one sorted by last name, the
  // other by first name
  by_last_name = newTree( memsys, sizeof( struct record ) );
  by_first_name = newTree( memsys, sizeof( struct record ) );

  // read names and phone numbers for the file, into record
  // add record to two different trees
  fp = fopen( "names1.txt", "r" );
  if (!fp)
  {
    fprintf( stderr, "Could not open \"names1.txt\"\n" );
    exit(-1);
  }

  fgets( buffer, 256, fp );	// skip header line

  while (!feof(fp))
  {
    result = fscanf( fp, "%s %s", record.first_name, record.last_name );
    result += fscanf( fp, "%s", record.phone_number );

    if (result==3)	// successful read of all 3 items in structure
    {
#ifdef DEBUG
      printf( "Adding %s, %s\n", record.last_name, record.first_name );
#endif

      // add the record to each tree
      addItem( memsys, by_last_name, comp_last_name, 
  	       &record );
      addItem( memsys, by_first_name, comp_first_name, 
  	       &record );
    }
  }
  fclose( fp );


  printf( "Trees built\n" );

  // look up last name Pollard
  strcpy( record.last_name, "Pollard" );
  if ( searchItem( memsys, by_last_name, comp_last_name, &record ) )
  {
    printf( "%s, %s.....%s\n", record.last_name, record.first_name, 
                               record.phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }


  // look up first name Frida
  strcpy( record.first_name, "Frida" );
  if ( searchItem( memsys, by_first_name, comp_first_name, &record ) )
  {
    printf( "%s, %s.....%s\n", record.last_name, record.first_name, 
                               record.phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }


  // look up last name Kremer
  strcpy( record.last_name, "Kremer" );
  if ( searchItem( memsys, by_last_name, comp_last_name, &record ) )
  {
    printf( "%s, %s.....%s\n", record.last_name, record.first_name, 
                               record.phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }


  freeTree( memsys, by_last_name );
  freeTree( memsys, by_first_name );

  printops( memsys );

  shutdown( memsys );
}
