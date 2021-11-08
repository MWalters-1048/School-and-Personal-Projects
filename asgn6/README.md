# Assignment 6

This program filters out bad words from text files. It will output all uses
of badwords and possible translations that were used in an input text file.

## Build

	$ clang -Wall -Wextra -Weror -Wpedantic -o -banhammer -banhammer.o -speck.o -hash.o -ll.o -node.o -bf.o -bv.o -parser.o
	
## Running
	
	$ ./banhammer -h <input> -f <input> -m 
	
	-h is the size of the hash table | default: 10000
	-f is the size of the bloom filter | default: 2^20
	-m will enable the move-to-front rule

## Cleaning

	rm -f banhammer *.o

## Format
	
	clang-format -i -style=file *.[ch]
