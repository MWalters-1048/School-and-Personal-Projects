CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: life

life: life.o universe.o
	$(CC) -o life life.o universe.o -lm

life.o: life.c
	$(CC) $(CFLAGS) -c life.c

universe.o: universe.c
	$(CC) $(CFLAGS) -c universe.c

debug: CFLAGS += -g
debug: clean all

clean:
	rm -f life *.o

format:
	clang-format -i -style=file *.[ch]

