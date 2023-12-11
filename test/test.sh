gcc -shared -fPIC -o libecraft.so ../*.c
gcc test.c -L. -lecraft -o test

export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

./test
