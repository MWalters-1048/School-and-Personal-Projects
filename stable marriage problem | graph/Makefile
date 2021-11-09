
da: da.o  graph.o List.o
	cc -o prog5 da.o graph.o List.o

da.o: da.c
	cc -c da.c

List.o: List.h List.c
	cc -c List.c

graph.o: graph.h graph.c List.o
	cc -c graph.c

clean:
	rm -f prog5 da da.o List.o graph.o

check:
	valgrind --leak-check=full ./prog5

