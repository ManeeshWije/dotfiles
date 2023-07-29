#include "a1.h"
#include <stdio.h>

int main( int argc, char **argv )
{
  unsigned short numbers[9] = {0,1,2,32767,32768,32769,65533,65534,65535};
  unsigned char bits[16];
  char bitstr[17];

  for (int pos=0;pos<9;pos++)
  {
    ushort2bits( numbers[pos], bits );
    bits2str( 16, bits, bitstr );

    printf( "%6d %s\n", numbers[pos], bitstr );
  }

  return 0;
}

