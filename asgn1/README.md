# Assignment 1

When This program is run it simulates the "garlic game" where vampires sit in a cirle
and roll dice. Whoever rolls the lowest is forced to eat garlic and lose a life.
The last vampire standing is the winner. 

## Build

	$ clang -Wall -Wextra -Weror -Wpedantic -o -vampire vampire.c
	
## Running 

	$ ./vampire
	
## Cleaning

	$ rm -f vampire vampire.o
	
## Format 
	
	$ clang-format -i -style=file *.[ch]
