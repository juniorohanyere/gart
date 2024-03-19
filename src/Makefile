# makefile to build object files from source files in src/

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
HEADER = gart.h

# dependency files
DEP = $(HEADER)

# prefix is based on system architecture
PREFIX = /usr

# include path
INC = ../include

# include directories
INCLUDE = -I$(INC)

# explicitly define macros
# -D_TTSPATH still under construction (to be later well defined)
MACRO = -D_ART=0 -D_INTERFACE=1 \
	-D_TTSPATH="\"$(shell pwd)/gtts.py"\"

# compiler flags
CFLAGS = $(INCLUDE) $(MACRO) -pedantic -std=gnu2x -Wall \
	 -Wdeclaration-after-statement -Werror -Wformat-security -Wextra

# target
TARGET = target

# target 0: dynamic/shared library
TARGET0 = libgart.so

# target 1: dynamic/shared library (graphical user interface)
TARGET1 = libgart-gui.so

# phony target
.PHONY: all clean clean-all

# default target
all: headers
	-$(MAKE) $(TARGET)
#	$(AR) x $(LIBNCURSES)
#	$(AR) x $(LIBTERMBOX)

$(TARGET): $(TARGET0)

$(TARGET0): $(OBJ)
	$(CC) -shared $^ -o $@

# copy headers to $(INC)
headers: $(DEP)
	@cp -v $^ $(INC)

# compiling each source file into a corresponding object file
%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# clean up generated object files
clean:
	@-rm -fv $(OBJ)

# clean up all generated files
clean-all:
	@-rm -fv $(wildcard *.o) $(TARGET0)
