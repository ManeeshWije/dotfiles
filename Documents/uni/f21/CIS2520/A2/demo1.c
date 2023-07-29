#include "memsys.h"
#include <stdio.h>

int main( int argc, char **argv )
{
  struct memsys *memsys;
  int ushort_ptr;
  unsigned short a=257, b;

  memsys = init(256,64);

  ushort_ptr = memmalloc( memsys, sizeof(unsigned short) );

  setval( memsys, &a, sizeof(unsigned short), ushort_ptr );

  getval( memsys, &b, sizeof(unsigned short), ushort_ptr );

  printf( "b=%d\n", b );

  print( memsys );

  memfree( memsys, ushort_ptr );

  print( memsys );

  shutdown( memsys );

  return 0;
}

