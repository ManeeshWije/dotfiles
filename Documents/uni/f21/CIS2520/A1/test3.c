#include "a1.h"
#include <stdio.h>

int main( int argc, char **argv )
{
  char *alpha = "abcde";
  unsigned char bits[8];

  for (int pos=0;pos<5;pos++)
  {
    printf( "%c ", alpha[pos] );
    char2bits( alpha[pos], bits );
    for (int bit=0;bit<8;bit++)
      printf( "%d", bits[bit] );
    printf( "\n" );
  }

  return 0;
}

