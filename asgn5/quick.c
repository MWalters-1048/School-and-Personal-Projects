//implementation of quicksort

// quicksort partition function

#include "quick.h"

#include "stack.h"

extern int compares;
extern int moves;

int partition(uint32_t *arr, int lo, int hi) {
    uint32_t tmp;
    uint32_t pivot = arr[lo + ((hi - lo) / 2)];
    int i = lo - 1;
    int j = hi + 1;

    while (i < j) {
        i++;
        while (arr[i] < pivot) {
            i++;
            compares++;
        }
        compares++;

        j--;
        while (arr[j] > pivot) {
            j--;
            compares++;
        }
        compares++;

        if (i < j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            moves += 3;
        }
    }
    return j;
}

void quick_sort(uint32_t *A, uint32_t n) {
    int64_t left = 0;
    int64_t right = n - 1;

    Stack *s = stack_create();
    stack_push(s, left);
    stack_push(s, right);

    int64_t hi, lo, p;

    while (!stack_empty(s)) {
        //stack_print(s);
        stack_pop(s, &hi);
        stack_pop(s, &lo);

        p = partition(A, lo, hi);
        if (p + 1 < hi) {
            stack_push(s, p + 1);
            stack_push(s, hi);
        }
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
        }
    }

    // clears stack after
    stack_delete(&s);
}
