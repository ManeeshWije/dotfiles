UNAME := $(shell uname)
CC = gcc
CFLAGS = -Wall -std=c11 -g
LDFLAGS= -L.

INC = include/
SRC = src/
BIN = bin/
OUT = ../
PARSER_SRC_FILES = $(wildcard src/SVG*.c)
PARSER_OBJ_FILES = $(patsubst src/SVG%.c,../SVG%.o,$(PARSER_SRC_FILES))

ifeq ($(UNAME), Linux)
	XML_PATH = /usr/include/libxml2
	LIB := ../libsvgparser.so
endif
ifeq ($(UNAME), Darwin)
	XML_PATH = /System/Volumes/Data/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/libxml2
	LIB := ../libsvgparser.dylib
endif

# parser: $(BIN)libsvgparser.so

$(LIB): $(PARSER_OBJ_FILES) $(OUT)LinkedListAPI.o
	gcc -shared -o $(LIB) $(PARSER_OBJ_FILES) $(OUT)LinkedListAPI.o -lxml2 -lm

#Compiles all files named SVG*.c in src/ into object files, places all corresponding SVG*.o files in bin/
$(OUT)SVG%.o: $(SRC)SVG%.c $(INC)LinkedListAPI.h $(INC)SVG*.h
	gcc $(CFLAGS) -I$(XML_PATH) -I$(INC) -c -fpic $< -o $@

$(OUT)liblist.so: $(OUT)LinkedListAPI.o
	$(CC) -shared -o $(OUT)liblist.so $(OUT)LinkedListAPI.o

$(OUT)LinkedListAPI.o: $(SRC)LinkedListAPI.c $(INC)LinkedListAPI.h
	$(CC) $(CFLAGS) -c -fpic -I$(INC) $(SRC)LinkedListAPI.c -o $(OUT)LinkedListAPI.o

clean:
	rm -rf $(OUT)*.o $(OUT)*.so $(OUT)*.dylib

###################################################################################################
