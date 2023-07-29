#ifndef _MEMSYS_H
#define _MEMSYS_H

#include <string.h>  // for size_t

#define BYTES_PER_LINE	32
#define MEMNULL -1

/* this represents a record of an allocated memory block inside the memrec
 * system
 */
struct memrec {
  int loc;	// index location in the memory
  int len;	// number of bytes allocated
  int used;	// currently in use (vs freed)
};

/* this represents a memory allocation system that is a simplified version
 * of those provided by operating systems
 */

struct memctr {	// a structure to hold 4 counters
  int malloc;
  int free;
  int set;
  int get;
};

struct memsys
{
  int capacity;		// total bytes of memory managed by the system
  void *memory;		// address of the memory managed by the system
  int mallocs;		// number of blocks of memory currently allocated
  int max_mallocs;	// maximum number of block of memory that can be
  			//	allocated
  struct memrec *table;	// table of memrec structures to track allocated memory
  struct memctr memctr; // operation counters
};

struct memsys *init( int capacity, int max_mallocs );
void shutdown( struct memsys *memsys_str );

int memmalloc( struct memsys *memsys, int bytes );
void memfree( struct memsys *memsys, int addr );

void getval( struct memsys *memsys_str, void *val, size_t size, int address );
void setval( struct memsys *memsys, void *val, size_t size, int address );

void printmem( struct memsys *memsys_str );
void printops( struct memsys *memsys_str );
void print( struct memsys *memsys_str );

#endif
