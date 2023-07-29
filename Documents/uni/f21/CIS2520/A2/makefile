all: array.o

array.o: array.c array.h memsys.h 
	clang -Wall -pedantic -std=c99 -c array.c -o array.o

clean:
	rm *.o
