#include "a1.h"
#include <stdio.h>

int main(int argc, char **argv) {
  char pontus[15] = "VENI VIDI VICI";

  caesar(pontus, 5);
  printf("%s\n", pontus);
  return 0;
}
