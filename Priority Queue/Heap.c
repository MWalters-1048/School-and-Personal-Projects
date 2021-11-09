// Implementation of (Max) Heap
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.h"

// TODO: Implement funcs for fetching parent and left/right child
int parent(int i) {
	return (i - 1) / 2;
}

int left(int i) {
	return (2 * i) + 1;
}

int right(int i) {
	return (2 * i) + 2;
}


//------------------------------------------------------------------------

// TODO: Helper function for swapping A[i] and A[j] elements in an array
void swap(int* A, int i, int j) {
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}


//------------------------------------------------------------------------

/* TODO: declare the Heap struct as in the header file
This Heap struc has the following fields:
- len: length of the array used for implementing the heap
- size: number of elements in the backbone array that are 'heapified' or ordered as heap
- array: (pointer to) array used for implementing the heap
*/

typedef struct Heap {
	int len;
	int size;
	int *array;
} Heap;



//------------------------------------------------------------------------

/* TODO: implement initializeHeap function which instantiates a heap using malloc.
This function takes in the following arguments:
- length of the array used for implementation
- size of the heap; i.e. number of elements in array that we want to be ordered as heap
- pointer to array used for implementing the heap
It returns a pointer to the instantiated heap
*/

Heap* initializeHeap(int len, int h_size, int* arr) {
	Heap *h = (Heap *)malloc(sizeof(Heap));

	h->len = len;
	h->size = h_size;
	h->array = arr;

	return h;
}




//------------------------------------------------------------------------


/*  TODO: implement heap destructor that frees memory allocated to heap */

void destructHeap(Heap* h) {
	free(h);
	h = NULL;
}


//------------------------------------------------------------------------

/* TODO: implement 'heapify' function, given a heap pointer and an index i
This function maintain (max) Heap property given an index i for heap h
*/


void heapify(Heap* h, int i) {
	int largest;
	int l = left(i);
	int r = right(i);

	if ((l < h->size) && (h->array[l] > h->array[i])) {
		largest = l;
	} else {
		largest = i;
	}

	if ((r < h->size) && (h->array[r] > h->array[largest])) {
		largest = r;
	}

	if (largest != i) {
		swap(h->array, i, largest);
		heapify(h, largest);
	}
}



//------------------------------------------------------------------------

/* TODO: implement array_to_heap function
You may use initializeHeap function for implementing this function
*/


Heap* array_to_Heap(int* A, int len, int size) {
	Heap* h = initializeHeap(len, size, A);

	size = len;
	for (int i = (len / 2); i > 0; i--) {
		heapify(h, i);
	}
}





//------------------------------------------------------------------------

/* TODO: implement utility functions:
- size(): returns the size field of a heap
- len(): returns the length field of a heap
*/

int size(Heap* h) {
	return h->size;
}

int len(Heap* h) {
	return h->len;
}













