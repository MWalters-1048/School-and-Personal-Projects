CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: prog0

prog0: prog0.o
	$(CC) -o prog0 prog0.o

prog0.o: prog0.c
	$(CC) $(CFLAGS) -c prog0.c

clean:
	rm -f prog0 *.o

format:
	clang-format -i -style=file *.[ch]
