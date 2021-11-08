# Assignment 4

All of the components of this program correct the errors that could occur if 
noise occured during data transfer.


## Build

	$ clang -Wall -Wextra -Weror -Wpedantic -o -gen generator.o hamming.o bm.o	
	
## Running
	
	./gen -i <input> | ./err -e <input> -s <input> | ./dec -o <input>
	
	-s is the seed which must be a positive integer
	-e the rate at which the program injects errors | default: 0.01
	-i the input file to be read | default: stdin
	-o the output file to print the stats of decoding function | default: stdout

##Cleaning

	rm -f gen dec err *.o

##Format
	
	clang-format -i -style=file *.[ch]
