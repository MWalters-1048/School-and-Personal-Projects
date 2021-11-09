CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: sorting

sorting: sorting.o bubble.o quick.o shell.o heap.o set.o stack.o
	$(CC) -o sorting sorting.o bubble.o quick.o shell.o heap.o set.o stack.o

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.[ch]







