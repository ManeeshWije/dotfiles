CC=clang
CFLAGS=-std=c99 -Wall -pedantic
EXECS=a4ttest 

all: $(EXECS)

clean:
	rm -i $($EXECS) *.o

# override the implicit compilation rules for executables so that we can
# override them with new ones
%: %.o
%: %.c



# compile a3test2.c using the ARRAY flag to use array operations
a4ttest.o:  a4ttest.c tree.h memsys.h
	$(CC) $(CFLAGS) -DARRAY -c a4ttest.c -o a4ttest.o


# create .o files by compiling the .c files
%.o : %.c memsys.h array.h tree.h
	$(CC) -c $(CFLAGS) $< -o $@

a4ttest: a4ttest.o tree.o memsys.o memsys.h tree.h
	$(CC) $(CFLAGS) memsys.o tree.o a4ttest.o -o a4ttest



