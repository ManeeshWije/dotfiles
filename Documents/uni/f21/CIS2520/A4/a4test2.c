#include "tree.h"
#include "memsys.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// function that compares records base (only) on first name
int comp( const void *ptr1, const void *ptr2 )
{
  const int *int1, *int2;

  int1 = ptr1;
  int2 = ptr2;

  return *int1 - *int2;
}



int main( int argc, char **argv )
{
  struct memsys *memsys;
  struct Tree *tree;
  int number;
  int addr;

  // initialize memsys with lots of ram and allocations 
  memsys = init(262144,512);

  // create two binary trees storing records, one sorted by last name, the
  // other by first name
  tree = newTree( memsys, sizeof( int ) );

  // attach a node holding 5 at the root
  number = 5;
  attachNode( memsys, &(tree->root), &number, sizeof(int) );

  // reset number
  number = 0;

  // read the root node
  readNode( memsys, &(tree->root), &number, sizeof(int) );

  printf( "Should print 5:  %d\n", number );

  printops(memsys);

  // add 1 on left branch
  number = 1;
  attachChild( memsys, &(tree->root), &number, sizeof(int), -1 );

  printf( "\nShould print a number and -1:\n" );
  printf( "Children of root:  %d %d\n", next( memsys, &(tree->root), -1 ),
                                        next( memsys, &(tree->root), +1 ) );

  printops(memsys);

  // add 8 based on binary search (should be right branch)
  number = 8;
  addItem( memsys, tree, comp, &number );

  printf( "\nShould print two numbers:\n" );
  printf( "Children of root:  %d %d\n", next( memsys, &(tree->root), -1 ),
                                        next( memsys, &(tree->root), +1 ) );

  printops(memsys);

  addr = next( memsys, &(tree->root), -1 );
  readNode( memsys, &(addr), &number, sizeof(int) );
  printf( "\nShould print 1: %d\n", number );

  printops(memsys);


  addr = next( memsys, &(tree->root), +1 );
  readNode( memsys, &(addr), &number, sizeof(int) );
  printf( "\nShould print 8: %d\n", number );

  printops(memsys);
  freeTree( memsys, tree );

  printops(memsys);
  shutdown( memsys );
}
