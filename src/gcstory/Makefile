# makefile to build object files from source files in src/cstory/

# compiler
CC = gcc

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
DEP = ../gart.h gcstory.h

# prefix is based on system architecture
PREFIX = /usr

# include path
INCLUDE = -I. -I..

# explicitly define macros
MACRO = -D_ART=1

# compiler flags
CFLAGS = $(INCLUDE) $(MACRO) -pedantic -std=gnu2x -Wall \
	 -Wdeclaration-after-statement -Werror -Wformat-security -Wextra -fPIC

# target
TARGET = target

# target 1: dynamic/shared library
TARGET1 = libgcstory.so

# target 2: static library
TARGET2 = libgcstory.a

# phony target
.PHONY: all clean clean-all

# default target
all: $(DEP)
	-$(MAKE) $(TARGET)
#	$(AR) x $(LIBNCURSES)
#	$(AR) x $(LIBTERMBOX)

$(TARGET): $(TARGET1)

$(TARGET1): $(OBJ)
	$(CC) -shared $^ -o $@

# compiling each source file into a corresponding object file
%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

# clean up generated object files
clean:
	-rm -f $(wildcard *.o)

# clean up all generated files
clean-all: clean
	-rm -f $(TARGET1)
