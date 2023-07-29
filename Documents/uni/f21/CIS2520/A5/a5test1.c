#include "hash.h"
#include "memsys.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STRLEN 128
#define TOTAL_RECORDS 100
#define CAPACITY 200

// record of names and phone numbers
struct record
{
  char last_name[STRLEN];
  char first_name[STRLEN];
  char phone_number[13];
};

void read_file( struct memsys *memsys, 
                int addr[TOTAL_RECORDS]  )
  // read the data file into memsys, record the addresses of the records in the
  // array addr
{
  FILE *fp;
  char buffer[ STRLEN ];
  int i;
  struct record record;

  // open the file
  fp = fopen( "names1.txt", "r" );

  // skip the first line
  fgets( buffer, STRLEN, fp );

  // read all the records (NO ERROR CHECKING!!!)
  for (i=0;i<TOTAL_RECORDS;i++)
  {
    // this code is not robust, buffer overflows or EOF not detected
    fscanf( fp, "%s %s", record.first_name, record.last_name );
    fscanf( fp, "%s", record.phone_number );

    // add record to hash table
    
    // allocate memory for record in memsys
    addr[i] = memmalloc( memsys, sizeof( struct record ) );

    // copy record info into memsys
    setval( memsys, &record, sizeof( struct record ), addr[i] );
  }

  fclose( fp );
}


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
  return  27;
}


int str2int( char *s, int max )
{
  char *c;

  unsigned long number, column, new;

  // convert string to base 28 number
  number = 0;
  column=1;

  for (c=s;(*c);c++)
  {
    number = char2int(*c) * column;
    column *= 28;
  }

  // convert number to a base max number and add up column values
  new = 0;
  while (number)
  {
    new = (new + (number % max)) % max;
    number = number / max;
  }

  printf( "%s -> %d\n", s, (int)new );
  return (int)new;

}

int hash_first_name( void *ptr, int max )
  // apply hash to first name of the record
{
  struct record *rec;

  rec = ptr;
  return str2int( rec->first_name, max );
}

int hash_last_name( void *ptr, int max )
  // apply hash to last name of the record
{
  struct record *rec;

  rec = ptr;
  return str2int( rec->last_name, max );
}

int comp_first_name( const void *ptr1, const void *ptr2 )
  // compare two records based on first name
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

int comp_last_name( const void *ptr1, const void *ptr2 )
  // compare two records based on last name
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
  int record[TOTAL_RECORDS];	// the records' addresses
  struct record tmp;            // tmp to hold search term
  int addr;	            	// address of item found

  struct memsys *memsys;
  struct HashTable *by_last_name;	// a HashTable based on last_name
  struct HashTable *by_first_name;	// a HashTable based on first_name

  int i;

  memsys = init(32768,512);

  // read names and phone numbers for the file, into record
  read_file( memsys, record );
  printf( "File read\n" );
  printf( "\n" );

  // create 2 HashTables and store all the records in them
  by_last_name = createTable( memsys, CAPACITY, sizeof( struct record ),
                              hash_last_name, comp_last_name );
  by_first_name = createTable( memsys, CAPACITY, sizeof( struct record ),
                              hash_first_name, comp_first_name );

  for (i=0;i<TOTAL_RECORDS;i++)
  {
    addElement( memsys, by_last_name, record[i] );
    addElement( memsys, by_first_name,record[i] );
  }

  printf( "Hashes built\n" );
  printops( memsys );
  printf( "\n" );



  // search by last_name == Pollard
  strcpy( tmp.last_name, "Pollard" );
  addr = getElement( memsys, by_last_name, &tmp );
  if (addr!=MEMNULL)
  {
    getval( memsys, &tmp, sizeof( struct record ), addr );
    printf( "%s, %s.....%s\n", tmp.last_name, tmp.first_name, 
                               tmp.phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }

  printops( memsys );
  printf( "\n" );

  // search by first_name == Frida
  strcpy( tmp.first_name, "Frida" );
  addr = getElement( memsys, by_first_name, &tmp );
  if ( addr!=MEMNULL )
  {
    getval( memsys, &tmp, sizeof( struct record ), addr );
    printf( "%s, %s.....%s\n", tmp.last_name, tmp.first_name, 
                               tmp.phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }

  printops( memsys );
  printf( "\n" );

  // search by last_name == Kremer
  strcpy( tmp.last_name, "Kremer" );
  addr = getElement( memsys, by_last_name, &tmp );
  if ( addr!=MEMNULL )
  {
    getval( memsys, &tmp, sizeof( struct record ), addr );
    printf( "%s, %s.....%s\n", tmp.last_name, tmp.first_name, 
                               tmp.phone_number );
  }
  else
  {
    printf( "Not found\n" );
  }

  printops( memsys );
  printf( "\n" );

  printf("Hash Accuracy Last name: %d\n", hashAccuracy(memsys, by_last_name));
  printf("Hash Accuracy first name %d\n", hashAccuracy(memsys, by_first_name));

  // freeTable( memsys, by_last_name );
  // freeTable( memsys, by_first_name );

  for (i=0;i<TOTAL_RECORDS;i++)
  {
    memfree( memsys, record[i] );
  }

  printf( "memory freed\n" );
  printops( memsys );
  printf( "\n" );

  shutdown( memsys );
}
