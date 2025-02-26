# A simple unit testing library
This is a minimal library for unit testing in C. It provides functions for running tests and checking assertions.

# Usage
Add the `testing.h` and `testing.c` files to your project, and include `testing.h` in the file that defines the main function that runs your unit tests. The `source` directory has an example that can be built using gcc with the `build_example.sh` script.

# Compatibility
This library assumes implementations of the `fork()` and `mmap()` POSIX functions are available. It uses these functions to run tests in their own child process to detect whether they fail due to a signal.
