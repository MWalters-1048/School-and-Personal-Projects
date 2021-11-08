//implementation of heap sort

#include "heap.h"

#include <stdbool.h>

extern int compares;
extern int moves;

//max_child
int max_child(uint32_t *arr, int first, int last) {
    int left = 2 * first;
    int right = left + 1;

    if (right <= last) {
        compares++;
        if (arr[right - 1] > arr[left - 1]) {
            return right;
        }
    }
    return left;
}

//fix_heap
void fix_heap(uint32_t *arr, int first, int last) {
    bool found = false;
    int parent = first;
    int great = max_child(arr, parent, last);
    int tmp;

    while (parent <= last / 2 && !found) {
        compares++;
        if (arr[parent - 1] < arr[great - 1]) {

            tmp = arr[parent - 1];
            arr[parent - 1] = arr[great - 1];
            arr[great - 1] = tmp;
            moves += 3;

            parent = great;
            great = max_child(arr, parent, last);
        } else {
            found = true;
        }
    }
}

//heapsort
void build_heap(uint32_t *arr, int first, int last) {
    for (int parent = last / 2; parent > first - 1; parent--) {
        fix_heap(arr, parent, last);
    }
}

//heap maintenance
void heap_sort(uint32_t *A, uint32_t n) {
    int first = 1;
    int last = n;
    build_heap(A, first, last);
    int tmp;

    for (int leaf = last; leaf > first; leaf--) {
        tmp = A[first - 1];
        A[first - 1] = A[leaf - 1];
        A[leaf - 1] = tmp;
        moves += 3;
        fix_heap(A, first, leaf - 1);
    }
}

//implementation of heap sort
