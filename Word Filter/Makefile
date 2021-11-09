CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: banhammer

banhammer: banhammer.o speck.o hash.o ll.o node.o bf.o bv.o parser.o 
	$(CC) -o banhammer banhammer.o speck.o hash.o ll.o node.o bf.o bv.o parser.o

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

hash.o: hash.c
	$(CC) $(CFLAGS) -c hash.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

clean:
	rm -f banhammer *.o

format:
	clang-format -i -style=file *.[ch]

