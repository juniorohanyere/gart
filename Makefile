# makefile to build object files from source files within the src directory

# compiler
CC = gcc

# archiver
AR = ar

# compiler flags
CFLAGS = -shared

# libraries for test target:
# should later use ecraft-config when it will be available
LIBS = -Lsrc -lecraft -Lsrc/cstory -lcstory \
	$(shell ncurses6-config --cflags --libs) -ltermbox -lespeak

# phony target
.PHONY: all clean clean-all

# default
all:
	-$(MAKE) -C src
	-$(MAKE) -C src/cstory

# test dynamic library
test:
	@$(CC) tests/test.c $(LIBS) -o tests/$@ -Wl,-rpath=$(shell pwd)
	@tests/$@

# test static library
test-static:
	@$(CC) -static tests/test.c $(LIBS) -o tests/$@
	@./tests/$@

# clean generated object files
clean:
	-$(MAKE) -C src clean
	-$(MAKE) -C src/cstory clean

# clean up all generated files
clean-all: clean
	-$(MAKE) -C src clean-all
	-$(MAKE) -C src/cstory clean-all
	-rm -f tests/test tests/test-static
