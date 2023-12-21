# makefile to build object files from source files within the src directory

# compiler
CC = gcc

# compiler flags
CFLAGS = -I. -pedantic -std=gnu2x -Wall -Wdeclaration-after-statement \
	-Werror -Wformat-security -Wextra

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

# static library to extract object files from
LIB = /usr/lib/x86_64-linux-gnu/libncurses.a
LIB2 = /usr/lib/x86_64-linux-gnu/libespeak.a

# default target
all: $(OBJ) $(LIB)
	$(AR) x $(LIB)
	$(AR) x $(LIB2)

# compiling each source file into an object file
%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# clean up generated files
clean:
	rm -f $(wildcard *.o)
