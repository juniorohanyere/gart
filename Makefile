# makefile to build object files from source files within the src directory

# compiler
CC = gcc

# archiver
AR = ar

# compiler flags
CFLAGS = -shared

# libraries for test target:
# should later use ecraft-config when it will be available
LIBS = -L. -lecraft $(shell ncurses6-config --cflags --libs) -ltermbox

# object files
OBJ = $(wildcard src/*.o)

# target
TARGET = target

# target file 1: dynamic library
TARGET1 = libecraft.so

# target file 2: static library
TARGET2 = libecraft.a

# default
all:
	$(MAKE) -C src
	$(MAKE) target

# make target
$(TARGET): $(TARGET1) $(TARGET2)

# build target by linking object files
$(TARGET1): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

# build target by archiving the object files
$(TARGET2): $(OBJ)
	$(AR) rcs $@ $^

# test target
test:
	$(CC) tests/test.c $(LIBS) -o tests/$@ -Wl,-rpath=.,-rpath=..
	./tests/test

# clean generated files
clean:
	$(MAKE) -C src clean
	rm -f $(TARGET1) $(TARGET2)
