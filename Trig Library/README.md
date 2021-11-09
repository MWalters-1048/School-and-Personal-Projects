# Assignment 2

mathlib.c is a collection of trigonometric functions that take an input x
and output a corresponding value based on what function it was passed through.

mathlib-test.c is a file that acts as a test harness for the functions written in mathlib.c.


## Build

	$ clang -Wall -Wextra -Weror -Wpedantic -o -mathlib-test mathlib-test.o mathlib.o
	
## Running 

	$ ./mathlib-test -a
	$ ./mathlib-test -s
	$ ./mathlib-test -c
	$ ./mathlib-test -t
	$ ./mathlib-test -e
	$ ./mathlib-test -l 
	
## Cleaning

	$ rm -f mathlib-test *.0
	
## Format 
	
	$ clang-format -i -style=file *.[ch]
	
