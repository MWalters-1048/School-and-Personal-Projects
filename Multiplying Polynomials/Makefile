CC = clang
CFLAGS = -Wall -Weror -Wextra -Wpedantic


all: prog1

prog1:	poly.o List.o
	$(CC) -o prog1 poly.o List.o

poly.o: List.h poly.c
	$(CC) -c poly.c

List.o: List.h List.c
	$(CC) -c List.c

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f prog1 poly.o List.o
