//implementation of shell sort
#include "shell.h"

#include "gaps.h"

extern int compares;
extern int moves;

void shell_sort(uint32_t *A, uint32_t n) {
    uint32_t tmp, gap, temp, j;
    for (uint32_t x = 0; x < GAPS; x++) {
        gap = gaps[x];
        for (uint32_t i = gap; i < n; i++) { // for i in range(gap, len(arr))
            j = i;
            temp = A[i];
            while (j >= gap && temp < A[j - gap]) {
                compares++;

                tmp = A[j - gap];
                A[j - gap] = A[j];
                A[j] = tmp;
                moves += 3;

                j -= gap;
            }

            if (j >= gap) {
                compares++;
            }

            A[j] = temp;
        }
    }
}
