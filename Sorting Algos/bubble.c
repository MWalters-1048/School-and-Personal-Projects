//implementation of bubble sort

#include "bubble.h"

#include <stdbool.h>

extern int compares;
extern int moves;

void bubble_sort(uint32_t *A, uint32_t n) {
    bool swapped = true;
    int temp;

    while (swapped) {
        swapped = false;
        for (uint32_t i = 1; i < n; ++i) {
            compares++;
            if (A[i] < A[i - 1]) {
                temp = A[i]; // temp = a
                A[i] = A[i - 1]; // a = b
                A[i - 1] = temp; // b = a
                moves += 3;

                swapped = true;
            }
        }
        n--;
    }
}
