#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Queue.h"
#include"Heap.h"
#include"PriorityQueue.h"

// Function signatures
void generateArrival(Queue* q, Heap* h, int pMax);
void processQueue(Queue* q, Heap* h, int* sumQ, int* sumPQ, int* processCount, int r);
void wildEvent(Heap* h, int pMax, int index);


/*
- generateArrival() would simulate stochastic arrival of events/packages
- to ensure replicability, it will only generate arrivals once //
there is room in the (priority) queue
- synced with processQueue, if an event is stochastically generated and
to be added, it will be added to both queue and priority queue
- the value/priority of the event is randomly generated from the
interval [1, pMax]
*/

void generateArrival(Queue* q, Heap* h, int pMax)
{
    if (size(h) == count(q) && size(h) < len(h)){
        int item = rand()%pMax + 1;
        enqueue(q, item);
        insert(h, item);
    }
}

/*
- processQueue() would simulate stochastic processing of events/packages
- we are assuming here that the rate of arrival/processing is equal to 'r'
- this means for each package/item that is processed, 'r' packages would arrive
- this is in average terms to capture the stochasticity of arrivals
- this means that if r > 1, the speed of arrivals is higher than processing
*/
void processQueue(Queue* q, Heap* h, int* sumQ, int* sumPQ, int* processCount, int r)
{
    if(rand()%r == 0 && count(q) > 0){
        int x = extract_max(h);
        (*sumPQ) += x;
        (*sumQ) += dequeue(q);
        (*processCount)++;
    }
}

/*
- wildEvent() simulates the case where at a random point in time, the value of
first element in the priority queue is increased/set to max value (pMax)

- Functionally, this is to ensure you've correctly implemented the 
increase_priority functionality

- This will also perturb you final result and useful for grading
*/

void wildEvent(Heap* h, int pMax, int index)
{
    increase_priority(h, index, pMax);
}



int main(void)
{   
    /* PARAMETERS:
    - pMax: maximum value/priority 10
    - r:    arrival/processing ratio 3
    - len:  length of the array in queue (for priority queue it's 'len-1' ) 11
    - seed: seed value for ensuring replicability 5 
    - iters: number of iterations in the simulations 20
    - timer: timer for activating wild event
    */
    // declaring the parameters
    int pMax, r, len, seed, iters;
    fscanf(stdin, "%d %d %d %d %d", &pMax, &r, &len, &seed, &iters);
    // setting the seed for replicability guarantees
    srand(seed);
    // declaring arrays for implementation of heap and queue ADTs
    int qarray[len];
    int harray[len-1];
    // set a random time for wild event
    int timer = rand()%iters;
    // (randomly) set the index of item whose priority would increase
    int index = rand()%(len - 1);    
    // initializing the heap
    Heap* h = initializeHeap(len-1, 0, harray);
    
    // initializing the queue
    Queue* q = initializeQueue(len,qarray);

    // declaring the sum of (processed) values for queue and priority queue
    int sumQ = 0;
    int sumPQ = 0;
    int processCount = 0;
    //running the clock
    for (int i = 0; i < iters; i++){
        // perform wild event when time is right i.e. i==timer
        if (i == timer){
            wildEvent(h, pMax, index);
        }
        generateArrival(q, h, pMax);
        processQueue(q, h, &sumQ, &sumPQ, &processCount, r);
    }

    printf("Average payoff of processed items after %d time periods using Queue is: %f\n", iters, (float)sumQ/processCount);
    printf("Average payoff of processed items after %d time periods using Priority Queue is: %f\n", iters, (float)sumPQ/processCount);
    
    // free memory allocated to queue and heap
    destructHeap(h);
    destructQueue(q);

    
    return 0;
}

