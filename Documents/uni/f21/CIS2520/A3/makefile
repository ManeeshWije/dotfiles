all: list.o

list.o: list.c list.h memsys.h
	clang -Wall -pedantic -std=c99 -c list.c -o list.o

clean: 
	rm *.o
