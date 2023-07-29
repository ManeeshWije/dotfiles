CC=clang
CFLAGS=-std=c99 -Wall -pedantic
EXECS=a5test1

all: $(EXECS)

clean:
	rm -i $($EXECS) *.o

# override the implicit compilation rules for executables so that we can
# override them with new ones
%: %.o
%: %.c



# compile a5test1.c using the ARRAY flag to use array operations
a5test1.o:  a5test1.c hash.h memsys.h
	$(CC) $(CFLAGS) -c a5test1.c -o a5test1.o


# create .o files by compiling the .c files
%.o : %.c memsys.h hash.h
	$(CC) -c $(CFLAGS) $< -o $@

a5test1: a5test1.o hash.o memsys.o memsys.h hash.h
	$(CC) $(CFLAGS) memsys.o hash.o a5test1.o -o a5test1




