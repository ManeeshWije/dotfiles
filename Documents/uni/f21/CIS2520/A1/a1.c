// Maneesh Wijewardhana #1125828
// CIS2520 A1
// 2021-09-21

#include "a1.h"

unsigned char checksum(char *string) {
  int val = 0;
  int final = 0;
  // loop that goes to the end of string until null. could have also used strlen
  // but pdf did not explicitly says so
  for (int i = 0; string[i] != '\0'; i++) {
    // using isupper to check which letters are uppercase. If they are, then
    // subtract the value 'A' from letter and add to total val
    // I do the same thing for islower except with lowercase 'a'
    if (isupper(string[i])) {
      val += string[i] - 'A';
    } else if (islower(string[i])) {
      val += string[i] - 'a';
    }
  }
  // final calculation for checksum
  final = val % 26;
  // making sure final value is never over 25 as stated in pdf
  if (final > 25) {
    printf("error\n");
  }
  return final;
}

void caesar(char *string, int rshift) {
  // loop to the end of string until null
  for (int i = 0; string[i] != '\0'; i++) {
    // making sure the letter is in between A and Z
    if (string[i] >= 'A' && string[i] <= 'Z') {
      // adding the shift provided from main
      string[i] += rshift;
      // wrapping around when shift makes letter go past Z
      if (string[i] > 'Z') {
        string[i] = string[i] - 'Z' + 'A' - 1;
        // substracting the value of 'z' and adding the value of 'a' -1 so that
        // the resulting char is again one in the selected range of a-z or A-Z
      }
    }
  }
}

void char2bits(char c, unsigned char bits[8]) {
  for (int i = 0; i < 8; i++) {
    bits[i] = get_bits8(i, i + 1, &c);
  }
}

void bits2str(int bitno, unsigned char *bits, char *bitstr) {
  for (int i = 0; i < bitno; i++) {
    bitstr[i] = bits[i] + '0';
  }
  bitstr[bitno] = '\0';
}

void ushort2bits(unsigned short s, unsigned char bits[16]) {
  for (int i = 0; i < 16; i++) {
    bits[i] = get_bits16(i, i + 1, &s);
  }
}

void short2bits(short s, unsigned char *bits) {
  for (int i = 0; i < 16; i++) {
    bits[i] = get_bits16(i, i + 1, &s);
  }
}

short bits2short(char *bits) {
  short temp = 0;  // to keep track
  short total = 0; // temp adds to this
  // looping to end of string using strlen as stated in pdf
  for (int i = 0; i < strlen(bits); i++) {
    if (bits[i] == '1') {
      temp = 1;
    }
    // in case the index is at the beginning and is 1, we know it has to be
    // negative
    if (bits[i] == '1' && i == 0) {
      temp = -1;
    }
    // loop for exponents
    for (int j = i + 1; j < strlen(bits); j++) {
      if (bits[i] == '0') {
        temp = 0;
      }
      // if the bit is 1, we keep multiplying temp by 2
      if (bits[i] == '1') {
        temp *= 2;
      }
    }
    // adding up temp to total
    total += temp;
    temp = 0; // we need to reinit temp to 0 so it can go back to the beginning
              // of the loop for the next one
  }
  return total;
}

void spff(char *sign, char *exponent, char *significand, float *src) {
  unsigned char bits[32];
  int counter = 0;
  int counter2 = 0;
  for (int i = 0; i < 32; i++) {
    // grabbing 32 bits from src
    bits[i] = get_bits32(i, i + 1, src);
  }
  // checking sign, if the first index is 1, sign is negative meaning '1'
  if (bits[0] == 1) {
    sign[0] = '1';
  } else {
    sign[0] = '0';
  }

  for (int i = 1; i < 9; i++) {
    // loop for exponent. we keep adding to counter each time an exponent is
    // added
    if (bits[i] == 1) {
      exponent[counter] = '1';
    } else {
      exponent[counter] = '0';
    }
    counter++;
  }

  for (int i = 9; i < 32; i++) {
    // loop for significand, same logic as exponent but instead we split from 9
    // to 32
    if (bits[i] == 1) {
      significand[counter2] = '1';
    } else {
      significand[counter2] = '0';
    }
    counter2++;
  }
}
