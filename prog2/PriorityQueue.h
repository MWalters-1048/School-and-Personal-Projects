//----------------------------------------------------
// PriorityQueue.h
// Header file for Priority Queue ADT
// Priority Queue implementation using a (max) heap
// ---------------------------------------------------

// Priority Queue Functionalities ---------------------------------------

// return max element in priority queue
int get_max(Heap* h);

// remove and return the max elemenet in priority queue
int extract_max(Heap* h);

// increase priority of element i to 'new_value'
void increase_priority(Heap* h, int i, int new_value);

// insert element with priority 'value' into the priority queue
void insert(Heap* h, int value);


