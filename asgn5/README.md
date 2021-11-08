# Assignment 5

This program runs specified sorting algorithms on randomly generated arrays.
The algorithms include quick sort, heap sort, bubble sort, and shell sort. 

## Build

	$ clang -Wall -Wextra -Weror -Wpedantic -o -sorting -sorting-o -bubble.o -quick.o -shell.o -heap.o -set.o -stack.o
	
## Running
	
	$ ./sorting -abshq -n <input> -r <input> -p <input>
	
	-abshq is the user specifying which algorithm to run | a: all, b: bubble, s: shell, h: heap, q: quick
	-n is the amount of randomly generated elements in the array you want to sort | default: 100
	-r is the input to seed the ranomly generated numbers | default: 7092016
	-p is how many elements you want to print out from the sorted array | default: 100

## Cleaning

	rm -f sorting *.o

## Format
	
	clang-format -i -style=file *.[ch]
