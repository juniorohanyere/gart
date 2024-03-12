# makefile to build object files from source files

# compiler
CC = gcc

# archiver
AR = ar

# compiler flags
CFLAGS = -shared

# libraries for test target:
# should later use gart-config when it will be available
LIBS = -Lsrc -lgart -Lsrc/gcstory -lgcstory \
       $(shell ncurses6-config --cflags --libs) -ltermbox

# phony target
.PHONY: all clean clean-all

# default
all:
	-$(MAKE) -C src
	-$(MAKE) -C src/gcstory

# test dynamic library
test:
	@$(CC) -Isrc -Isrc/gcstory -D_ART=1 tests/test.c $(LIBS) -o tests/$@ \
	-Wl,-rpath=$(shell pwd)/src,-rpath=$(shell pwd)/src/gcstory
	@tests/$@

# test static library
# test-static:
#	@$(CC) -static tests/test.c $(LIBS) -o tests/$@
#	@./tests/$@

# clean up generated object files
clean:
	-$(MAKE) -C src clean
	-$(MAKE) -C src/gcstory clean

# clean up all generated files
clean-all: clean
	-$(MAKE) -C src clean-all
	-$(MAKE) -C src/gcstory clean-all
	-rm -f tests/test tests/test-static
