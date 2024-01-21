# makefile to build object files from source files within the src directory

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

# header file
HEADER = cstory.h

# dependency files
DEP = ../ecraft.h $(HEADER)

# prefix is based on system architecture
PREFIX = /usr

# inlcude directories
INCLUDE = -I. -I..

# include path
INC = ../../include

# explicitly define macros
MACRO = -D_CRAFT=1

# compiler flags
CFLAGS = $(INCLUDE) $(MACRO) -pedantic -std=gnu2x -Wall \
	-Wdeclaration-after-statement -Werror -Wformat-security -Wextra -fPIC

# target
TARGET = target

# target 1: dynamic/shared library
TARGET1 = libcstory.so

# target 2: static libarary
TARGET2 = libcstory.a

# phony target
.PHONY: all clean clean-all

# default target
all: $(DEP)
	-$(MAKE) $(TARGET)
#	$(AR) x $(LIBNCURSES)

$(TARGET): $(TARGET1)

$(TARGET1): $(OBJ)
	@cp -v $(HEADER) $(INC)
	$(CC) -shared $^ -o $@

# compiling each source file into an object file
%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

# clean up generated object files
clean:
	@-rm -fv $(wildcard *.o)

# clean up all generated files
clean-all: clean
	@-rm -fv $(TARGET1)
