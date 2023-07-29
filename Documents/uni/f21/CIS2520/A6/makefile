all: a6

a6: a6.o hash.o
	clang -Wall -pedantic -std=c99 a6.o hash.o -o a6

a6.o: a6.c
	clang -Wall -pedantic -std=c99 -c a6.c

hash.o: hash.c hash.h 
	clang -Wall -pedantic -std=c99 -c hash.c 

clean:
	rm *.o
