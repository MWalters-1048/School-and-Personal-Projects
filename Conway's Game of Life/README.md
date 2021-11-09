# Assignment 3

This program simulates The Game of Life which is played on a 2D grid of cells
that represent a universe. As the generations of the game are played out, 
the values of the cells change based on rules of the game. 

## Build

	$ clang -Wall -Wextra -Weror -Wpedantic -o -life life.o universe.o	
	
## Running
	
	./life -t -s -n <input> -i <input> -o <input>
	
	-t is if you want the game to be played on a toroidal universe
	-s if enabled, nothing will be displayed by ncurses
	-n is the number of generations that the universe will go through | default: 100
	-i the input file to be read to populate the universe | default: stdin
	-o the output file to print the final state of the universe | default: stdout

##Cleaning

	rm -f life *.o

##Format
	
	clang-format -i -style=file *.[ch]
