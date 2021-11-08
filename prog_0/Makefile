CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: shoulders

shoulders: shoulders.o
	$(CC) -o shoulders shoulders.o

shoulders.o: shoulders.c
	$(CC) $(CFLAGS) -c shoulders.c

clean:
	rm -f shoulders shoulders.o

format:
	clang-format -i -style=file *.[ch]
