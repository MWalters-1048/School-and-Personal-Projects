CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: gen dec err

gen: generator.o hamming.o bm.o
	$(CC) -o gen generator.o hamming.o bm.o

dec: decoder.o hamming.o bm.o
	$(CC) -o dec decoder.o hamming.o bm.o

err: error.c
	$(CC) -o err error.c 

generator.o: generator.c
	$(CC) $(CFLAGS) -c generator.c

decoder.o: decoder.c
	$(CC) $(CFLAGS) -c decoder.c

hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c

clean:
	rm -f gen dec err *.o

format:
	clang-format -i -style=file *.[ch]
