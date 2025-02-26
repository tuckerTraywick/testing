#/bin/sh
rm -f run_example
gcc source/testing.c source/example.c -Iinclude -o run_example
