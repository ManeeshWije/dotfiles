all: hash.o

hash.o: hash.c hash.h memsys.h
	clang -Wall -pedantic -std=c99 -c hash.c -o hash.o

clean: 
	rm *.o
