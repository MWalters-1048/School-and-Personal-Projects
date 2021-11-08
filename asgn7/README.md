# Assignment 7

This program performs LZ78 file compression and decompression.

## Build

	$ make
	$ make clean
	$ make format
	
## Running
	
	$ ./encode -i <input> -o <input> -v 
	$ ./decode -i <input> -o <input> -v 
	
	-i is the input file
	-o is the output file
	-v prints compression/decompression statistics

## Cleaning

	rm -f encode decode *.o

## Format
	
	clang-format -i -style=file *.[ch]
	
## Scan-build error

	scan-build identifies an error that a variable is unused even though I use/assign a value to that 
	variable a few lines later. 
