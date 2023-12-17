# makefile to build object files from source files within the src directory

# compiler
CC = gcc

# compiler flags
CFLAGS = -pedantic -std=gnu2x -Wall -Wdeclaration-after-statement -Werror \
	-Wextra

# archiver
AR = ar

# all source files
SRCS = $(wildcard *.c)

# exclude files
EXCLUDE = # files to exclude

# source files
SRC = $(filter-out $(EXCLUDE), $(SRCS))

# object files
OBJ = $(patsubst %.c, %.o, $(SRC))

# dependency files
DEP = ecraft.h

# static library to extract from
LIB = $(shell whereis libncurses.a | awk '{print $$2}')

# default target
all: $(OBJ) $(LIB)
	$(AR) x $(LIB)

# compiling each source file into an object file
%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# clean up generated files
clean:
	rm -f $(wildcard *.o)
