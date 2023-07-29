#include <stdlib.h>
#include <string.h>  // for size_t
#include <stdio.h>

#include "memsys.h"

/******************************************************************************/
// memsys.c Version 1.10
/******************************************************************************/

struct memsys *init( int capacity, int max_mallocs )
  /* initialize the memsys system
   * capacity - is the total number of bytes to be allocated
   * max_mallocs - is the number of mallocs that are allowed
   */
{
  struct memsys *memsys_str;

  // allocate the memsys structure
  memsys_str = malloc( sizeof( struct memsys ) );
  if (!memsys_str)
    return NULL;

  // allocate the user storage within the memsys structure
  memsys_str->memory = malloc( capacity );
  if (!memsys_str->memory)
  {
    free( memsys_str );
    return NULL;
  }

  // allocate the allocation table based on the max_mallocs
  memsys_str->table = (struct memrec *)malloc( sizeof(int)*3*max_mallocs );
  if (!memsys_str->table)
  {
    free( memsys_str->memory );
    free( memsys_str );
    return NULL;
  }

  // record the initial parameters
  memsys_str->capacity = capacity;
  memsys_str->mallocs = 0;
  memsys_str->max_mallocs = max_mallocs;

  // reset the counters
  memsys_str->memctr.malloc = 0;
  memsys_str->memctr.free = 0;
  memsys_str->memctr.set = 0;
  memsys_str->memctr.get = 0;

  // return the structure ready for use
  return memsys_str;
}

/******************************************************************************/
void shutdown( struct memsys *memsys_str )
  /*
   * Shut down the memory allocation system.
   * memsys_str - is the memory system struture pointer
   */
{
  // free the 3 mallocs in init
  free( memsys_str->table );
  free( memsys_str->memory );
  free( memsys_str );
}

/******************************************************************************/
int memmalloc( struct memsys *memsys, int bytes )
  /*
   * Allocate a block of memory in the memsys system.
   * memsys - memory system structure
   * bytes - number of bytes to allocate
   */
{
  int block;
  struct memrec *prev, *new;

  // look for an unused block of sufficient size
  for (block=0;block<memsys->mallocs;block++)
  {
    if (memsys->table[block].len >= bytes && !memsys->table[block].used)
    {
      memsys->table[block].used = 1;
      return memsys->table[block].loc;
    }
  }
  // couldn't find one

  if (memsys->mallocs)	// if there are previously allocated blocks
  { 
    // find last block 
    prev = memsys->table + memsys->mallocs - 1;
    // and new block
    new = prev + 1;

    new->loc = prev->loc + prev->len;
    new->len = bytes;
  }
  else // this is the very first memory block
  {
    // put it at the beginning of the table
    new = memsys->table;
    new->loc = 0;
    new->len = bytes;
  }

  // check if there's enough memory
  if (new->loc+new->len > memsys->capacity)
    return MEMNULL;

  // increment allocated blocks
  memsys->mallocs++;

  // mark the new block as used
  new->used = 1;

  // increment malloc counter
  memsys->memctr.malloc++;

  // return the location of the new block
  return new->loc;
} 

/******************************************************************************/
void memfree( struct memsys *memsys, int addr )
  /*
   * free memory allocated by memmalloc
   * memsys - the point to the memory system structure
   * addr - address (in memsys) of memory to free
   */
{
  if (addr==MEMNULL)
    return;	// just like the real free

  // find the block
  for (int block=0;block<memsys->mallocs;block++)
  {
    if (memsys->table[block].loc == addr)
    {
      // mark is as unused
      memsys->table[block].used = 0;

      // increment free counter
      memsys->memctr.free++;

      return;
    }
  }

  // block not found
  fprintf( stderr, "Segmentation fault\n" );
  exit(-1);
}

/******************************************************************************/
void setval( struct memsys *memsys, void *val, size_t size, int address )
  /* set a value inside the mymsys structure
   * memsys - pointer to memsys structure
   * val - pointer to source of the value
   * size - size in bytes of the value
   * address - destination of the value
   */
{
  char *ptr;

  // check for valid address
  if (address<0 || address>=memsys->capacity)
  {
    fprintf( stderr, "Segmentation fault\n" );
    exit(-1);
  }

  // find the beginning of memsys memory
  ptr = memsys->memory;

  // copy the data
  memcpy( ptr+address, val, size );

  // update counter
  memsys->memctr.set++;
}

/******************************************************************************/
void getval( struct memsys *memsys, void *val, size_t size, int address )
  /* get a value inside the mymsys structure
   * memsys - pointer to memsys structure
   * val - pointer to destination of the value
   * size - size in bytes of the value
   * address - source of the value
   */
{
  char *ptr;

  // check that the address is valid
  if (address<0 || address>=memsys->capacity)
  {
    fprintf( stderr, "Segmentation fault\n" );
    exit(-1);
  }

  // find start of memsys memory
  ptr = memsys->memory;

  // copy data
  memcpy( val, ptr+address, size );

  // increment pointer
  memsys->memctr.get++;
}

/******************************************************************************/

void printmem( struct memsys *memsys )
  /* print pretty tables showing the data, the allocated blocks and the
   * operation counters
   * memsys - pointer to memsys structure
   */
{
  unsigned char *ptr;
  int i;

  printf("Memory map:\n");
  for ( ptr=memsys->memory, i=0;
       i<memsys->capacity;
       ptr++,i++)
  {
    if (i%BYTES_PER_LINE==0)
      printf( "%06x: ", i );
    printf( "%02x", *ptr );
    if ((i+1)%BYTES_PER_LINE==0)
      printf( "\n" );
  }

  printf("\nMemory allocation:\n");
  for (i=0;i<memsys->mallocs;i++)
  {
    if (memsys->table[i].used)
      printf( "%03d %06x %d\n", i, memsys->table[i].loc, memsys->table[i].len );
  }
}

/******************************************************************************/

void printops( struct memsys *memsys )
{
  printf("\nOperations:\n");
  printf("  malloc: %3d\n", memsys->memctr.malloc );
  printf("  free:   %3d\n", memsys->memctr.free );
  printf("  set:    %3d\n", memsys->memctr.set );
  printf("  get:    %3d\n", memsys->memctr.get );
}


/******************************************************************************/

void print( struct memsys *memsys )
{
  printmem( memsys );
  printops( memsys );
}
