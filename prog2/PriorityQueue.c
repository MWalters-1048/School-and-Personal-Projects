#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.c"
#include"PriorityQueue.h"

/* TODO: implement get_max
returns largest element in heap/highest priority
*/

int get_max(Heap* h) {
	return h->array[0];
}

//------------------------------------------------------------------------

/* TODO: implement extract_max
extracts and returns max element in heap
note that heap property must be maintained after extraction
also check for valid input (cannot extract from empty heap)
*/

int extract_max(Heap* h) {
	if (h->size < 1) {
		//fix
		fprintf(stderr, "heap underflow\n");
		exit(-1);
	}

	int max = h->array[0];
	h->array[0] = h->array[h->size - 1];
	h->size = h->size - 1;
	heapify(h, 0);
	return max;
}


//------------------------------------------------------------------------

/* TODO: implement increase_priority
This function increases priority/value of element at index i to 'new_value'
*/

void increase_priority(Heap* h, int i, int new_value) {
//	if (new_value < h->array[i]) {
//		fprintf(stderr, "new value is smaller than current value\n");
//		exit(-1);
//	}

	h->array[i] = new_value;

	while ((i > 0) && (h->array[parent(i)] < h->array[i])) {
		swap(h->array, i, parent(i));
		i = parent(i);
	}
}




//------------------------------------------------------------------------

/* TODO: implement insert functionality
This function inserts priority 'value' into heap
You will need to have implemented the increase_priority and use it here
*/

void insert(Heap* h, int value) {
	h->size = h->size + 1;
	h->array[h->size] = -1; // -inf
	increase_priority(h, h->size - 1, value);
	return;
}



