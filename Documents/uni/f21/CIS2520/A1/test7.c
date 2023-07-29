#include "a1.h"
#include <stdio.h>

int main(int argc, char **argv) {
  short numbers[9] = {-32768, -32767, -32766, -1, 0, 1, 32765, 32766, 32767};
  unsigned char bits[16];
  char bitstr[17];
  short number;

  for (int pos = 0; pos < 9; pos++) {
    short2bits(numbers[pos], bits);
    bits2str(16, bits, bitstr);
    number = bits2short(bitstr);

    printf("%6d %s %6d\n", numbers[pos], bitstr, number);
  }

  return 0;
}
