CC=clang
CFLAGS=-std=c99 -Wall -pedantic
EXECS=alphanim

all: $(EXECS)

clean:
	rm -i $($EXECS) *.o

# override the implicit compilation rules for executables so that we can
# override them with new ones
%: %.o
%: %.c



alphanim:  alphanim.o nim.h nim.o nimhelp.o
	$(CC) $(CFLAGS) alphanim.o nim.o nimhelp.o -o alphanim

# create .o files by compiling the .c files
# create .o files by compiling the .c files
%.o : %.c nim.h
	$(CC) -c $(CFLAGS) $< -o $@





