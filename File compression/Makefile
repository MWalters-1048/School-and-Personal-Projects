CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic 

all: encode decode

encode: encode.o trie.o io.o endian.o
	$(CC) -o encode encode.o trie.o io.o

decode: decode.o word.o io.o endian.o 
	$(CC) -o decode decode.o word.o io.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

trie.o: trie.c
	$(CC) $(CFLAGS) -c trie.c

word.o: word.c
	$(CC) $(CFLAGS) -c word.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

endian.o: endian.h
	$(CC) $(CFLAGS) -c endian.h

clean:
	rm -f encode decode *.o

format:
	clang-format -i -style=file *.[ch]
