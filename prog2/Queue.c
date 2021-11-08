#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Queue.h"
// Implemeting Queue

/* 
TODO: define the Queue structure using 'typedef struct Queue' - this queue holds integer values
the Queue struct has the following fields:
- head: corresponding to the head of the queue
- tail: indicating the tail of the queue
- length: length of the array used for implementing the queue
- count: number of elements in the queue
- array: (pointer to) the array used for implementing the queue
*/

typedef struct Queue {
	int head;
	int tail;
	int length;
	int count;
	int *array;
} Queue;



//------------------------------------------------------------------------

/*
TODO: implement the initializeQueue - this function instantiates the Queue struct using malloc and sets the values for the fields.
Arguments to this function are:
- int* arr: (pointer to) array 'arr' that is used for implementing the queue
- int n: length of array 'arr'
It returns a pointer to the instantiated Queue
*/

Queue* initializeQueue(int n, int *arr) {
	Queue *q = (Queue *)malloc(sizeof(Queue));
	
	q->length = n;
	q->head = 0;
	q->tail = 0;
	q->count = 0;
	q->array = arr;

	return q;
}



//------------------------------------------------------------------------

/*
TODO: implement Queue destructor - this function frees memory allocated to Queue
Argument to this function is a queue pointer
*/

void destructQueue(Queue *q) {
	free(q);
	q = NULL;
}




//------------------------------------------------------------------------

/* TODO: implement the 'enqueue' functionality
This function takes in a queue pointer and int value 'x' and adds 'x' to queue
Need to check for overflow

*/


void enqueue(Queue* q, int x) {
	// check overflow
	if (q->count == (q->length - 1)) {
		return;
	}
	
	// inserting the input at the tail
	q->array[q->tail] = x;

	// if tail at the end, move it to front, else increment tail
	if (q->tail == (q->length - 1)) {
		q->tail = 0;
	} else {
		q->tail = q->tail + 1;
	}

	// increment counter 
	q->count = q->count + 1;
}



//------------------------------------------------------------------------

/* TODO: implement the 'dequeue' functionality
This function takes in a queue pointer and removes element from head of the queue
Need to check for underrflow
*/

int dequeue(Queue* q) {
        if (q->count == 0) {
		fprintf(stderr, "empty queue\n");
                exit(-1);
        }

        int ret_val = q->array[q->head];

        if (q->head == q->length - 1) {
                q->head = 0;
        } else {
                q->head = q->head + 1;
        }

        q->count = q->count - 1;

        return ret_val;
}




//------------------------------------------------------------------------

/* TODO: implement the printQueue
This function takes in a queue pointer and prints the contents of the queue in order (head to tail)
Note: this is a non-trivial function
*/

void printQueue(Queue* q) {
        if (q->head < q->tail) {
                for (int i = q->head; i < q->count; i++) {
                        printf("%d ", q->array[i]);
                }
                printf("\n");
        }

        if (q->head > q->tail) {
                for (int i = q->tail; i < q->head; i++) {
                        printf("%d ", q->array[i]);
                }
                printf("\n");
        }
        return;
}


//------------------------------------------------------------------------

/* TODO: implement the count
This function takes in a queue pointer and returns the 'count' field of the queue
Implementing this is necessarity for the simulator to run properly
*/


int count(Queue* q) {
	return q->count;
}




