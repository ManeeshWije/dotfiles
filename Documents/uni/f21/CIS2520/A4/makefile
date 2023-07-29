all: tree.o

tree.o: tree.c tree.h memsys.h
	clang -Wall -pedantic -std=c99 -c tree.c -o tree.o

clean: 
	rm *.o
