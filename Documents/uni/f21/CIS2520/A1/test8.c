#include "a1.h"
#include <stdio.h>
#include <stdlib.h>


int main( int argc, char **argv )
{
  // a bunch of numbers to convert, the first is from the wikipedia article
  float x[5] = { 0.15625, -0.15625, 0.1875, 0.171875, 0.3125 };

  char sign[2];
  char exponent[9];
  char fraction[24];

  for (int i=0;i<5;i++)
  {
    spff(sign,exponent,fraction,&(x[i]));

    printf( "%9.6f %s %s %s\n", x[i], sign, exponent, fraction );
  }
  return 0;
}

