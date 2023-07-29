#include "get_bits.h"

unsigned char get_bits8(unsigned char from, unsigned char to, void *data)
/* This function returns the numeric value of a series of bits in memory.
 * The memory location is given by "data", and the bits returned are in
 * most-significant to least-significant order starting at "from" and going
 * upto, but not including "to".  "data" must contain the memory address
 * of one byte of readable data.
 * Example:  if data points to a memory address storing the value:
 *           212 (base 10) = 11010100 (base 2)
 * Then the bits would be numbered as follows:
 *           [0][1][2][3][4][5][6][7]
 *            1  1  0  1  0  1  0  0
 * If from=1 and to=6, then bits [1] to [5] would be retreived
 *              [1][2][3][4][5]
 *               1  0  1  0  1
 * and the value returned by this function would be:
 *           10101 (base 2) = 21
 */
{
  unsigned char val = 0;     // value to be returned
  unsigned char *ptr = data; // pointer to the first byte of data

  val = *ptr;                   // copy the data into val
  val = val << from;            // push the bits left, dropping "from" bits
  val = val >> (from + 8 - to); // push the bits right, dropping 8-to bits

  return val; // return a value equal to the selected bits
}

unsigned short get_bits16(unsigned char from, unsigned char to, void *data)
/* This function returns the numeric value of a series of bits in memory.
 * The memory location is given by "data", and the bits returned are in
 * most-significant to least-significant order starting at "from" and going
 * upto, but not including "to".  "data" must contain the memory address
 * of two bytes of readable data.
 */
{
  unsigned short val = 0;     // value to be returned
  unsigned short *ptr = data; // pointer to the first two bytes of data

  val = *ptr;                    // copy the data into val
  val = val << from;             // push the bits left, dropping "from" bits
  val = val >> (from + 16 - to); // push the bits right, dropping 16-to bits

  return val; // return a value equal to the selected bits
}

unsigned int get_bits32(unsigned char from, unsigned char to, void *data)
/* This function returns the numeric value of a series of bits in memory.
 * The memory location is given by "data", and the bits returned are in
 * most-significant to least-significant order starting at "from" and going
 * upto, but not including "to".  "data" must contain the memory address
 * of four bytes of readable data.
 */
{
  unsigned short val = 0;     // value to be returned
  unsigned short *ptr = data; // pointer to the first two bytes of data

  val = *ptr;                    // copy the data into val
  val = val << from;             // push the bits left, dropping "from" bits
  val = val >> (from + 32 - to); // push the bits right, dropping 32-to bits

  return val; // return a value equal to the selected bits
}

unsigned long get_bits64(unsigned char from, unsigned char to, void *data)
/* This function returns the numeric value of a series of bits in memory.
 * The memory location is given by "data", and the bits returned are in
 * most-significant to least-significant order starting at "from" and going
 * upto, but not including "to".  "data" must contain the memory address
 * of eight bytes of readable data.
 */
{
  unsigned short val = 0;     // value to be returned
  unsigned short *ptr = data; // pointer to the first two bytes of data

  val = *ptr;                    // copy the data into val
  val = val << from;             // push the bits left, dropping "from" bits
  val = val >> (from + 64 - to); // push the bits right, dropping 64-to bits

  return val; // return a value equal to the selected bits
}
