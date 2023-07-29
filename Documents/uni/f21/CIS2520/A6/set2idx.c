#include <stdio.h>

int main( int argc, char **argv )
{
  char boolean;

  FILE *fp = fopen( argv[1], "rb" );

  for (int i=0; fread(&boolean,1,1,fp)==1; i++)
  {
    if (boolean)
      printf( "%d\n", i );
  }

  return 0;
}
