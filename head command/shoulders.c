#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h> 


void processfile(int fd, int lines);


int main(int argc, char *argv[]) {

	//number of lines to print 
	char* endptr = NULL;
	int numlines = strtol(argv[1], &endptr, 10);
	if (*endptr) {
		fprintf(stderr, "%s: invalid number of lines: '%s'\n", argv[0], argv[1]);
		return 0;
	}
	
	if (numlines < 0) {
		return 0;
	}

	if (argc == 2) {
		processfile(STDIN_FILENO, numlines);
		return 0;
	}
	
	//loop for all the command line arguments (files)
	for (int i = 2; i < argc; i++) {

		int fd;

		if (!strcmp(argv[i], "-")) {
			fd = STDIN_FILENO;
			processfile(fd, numlines);
		} else {
			fd = open(argv[i], O_RDONLY);
			if (fd == -1) {
				warn("cannot open '%s' for reading", argv[i]);
				//fprintf(stderr, "%s: cannot open '%s' for reading: %s\n", argv[0], argv[i], strerror(errno));
				return 0;
			}
			processfile(fd, numlines);
			close(fd);
		}
			
	}
	return 0;
}

void processfile(int fd, int lines) {
	char buffer[4096];

	//if fd is no files
	//print from sdtin until runs out of input or desired # of lines
	int j = 0;
	while (j < lines) {

		int bytes_read = read(fd, buffer, 4096);
	
		if (bytes_read == 0) {
			break;
		}
	
		if (bytes_read == -1) {
			//error
		}
	
		int start = 0;
		for (int k = 0; k < bytes_read; k++) {
			if (buffer[k] == '\n') {
				write(STDOUT_FILENO, &buffer[start], k - start);
				j++;

				//start keeps track of where last newline was
				start = k;
		
				//if all lines printed then break
				if (j == lines) {
					write(STDOUT_FILENO, "\n", 1);
					break;
				}
			}
		}
	
		//if more lines to be printed, then print the rest of buffer
		// ie start of current line
		if (j < lines) {
			write(STDOUT_FILENO, &buffer[start], bytes_read - start);
		}
	}
}

