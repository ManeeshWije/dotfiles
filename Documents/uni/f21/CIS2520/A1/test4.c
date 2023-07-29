#include "a1.h"
#include <stdio.h>

int main(int argc, char **argv) {
  char *alpha = "abcde";
  unsigned char bits[8];
  char bitstr[9];

  for (int pos = 0; pos < 5; pos++) {
    char2bits(alpha[pos], bits);
    bits2str(8, bits, bitstr);

    printf("%c %s\n", alpha[pos], bitstr);
  }

  return 0;
}
