all: nim.o

nim.o: nim.c nimhelp.c alphanim.c nim.h
	clang -Wall -pedantic -std=c99 nim.c alphanim.c nimhelp.c -o nim.o 
	
clean:
	rm *.o

