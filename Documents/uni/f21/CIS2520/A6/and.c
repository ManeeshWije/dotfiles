#include <stdio.h>

int main( int argc, char **argv )
{
  FILE *fp1 = fopen( argv[1], "rb" );
  FILE *fp2 = fopen( argv[2], "rb" );
  FILE *fp3 = fopen( argv[3], "wb" );
  char b1, b2, b3;

  while ( fread( &b1, 1, 1, fp1 )==1 && fread( &b2, 1, 1, fp2 ) )
  {
    b3 = b1&&b2;
    fwrite( &b3, 1, 1, fp3 );
  }

  fclose( fp1 );
  fclose( fp2 );
  fclose( fp3 );

  return 0;
}
