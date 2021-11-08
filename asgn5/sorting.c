// contains main()

#include "bubble.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "absqhr:n:p:"

int compares;
int moves;

typedef enum sort_func { bubble, shell, quick, heap, num_sorts } sort_func;

int main(int argc, char **argv) {
    int seed = 7092016;
    int array_size = 100;
    int n_to_print = 100;

    Set sort_set = set_empty();

    // getopts
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            sort_set = set_insert(sort_set, bubble);
            sort_set = set_insert(sort_set, shell);
            sort_set = set_insert(sort_set, quick);
            sort_set = set_insert(sort_set, heap);
            break;

        case 'b': sort_set = set_insert(sort_set, bubble); break;

        case 's': sort_set = set_insert(sort_set, shell); break;

        case 'q': sort_set = set_insert(sort_set, quick); break;

        case 'h': sort_set = set_insert(sort_set, heap); break;

        case 'r': seed = atoi(optarg); break;

        case 'n': array_size = atoi(optarg); break;

        case 'p': n_to_print = atoi(optarg); break;
        }
    }

    // if elements to print is greater than array size
    if (n_to_print > array_size) {
        n_to_print = array_size;
    }

    srandom(seed);
    uint32_t *arr = malloc(array_size * sizeof(uint32_t));
    uint32_t *arr2 = malloc(array_size * sizeof(uint32_t));

    for (int i = 0; i < array_size; i++) {
        arr[i] = random() & 0x3FFFFFFF; // mask 30 bits
        arr2[i] = arr[i];
    }

    for (int i = bubble; i < num_sorts; i++) {
        if (set_member(sort_set, i)) {
            switch (i) {
            case bubble:
                moves = 0;
                compares = 0;
                bubble_sort(arr, array_size);
                printf("Bubble Sort\n");
                printf("%d elements, %d moves, %d compares", array_size, moves, compares);

                for (int x = 0; x < n_to_print; x++) {
                    if (!(x % 5)) {
                        putchar('\n');
                    }
                    printf("%13" PRIu32, arr[x]); // newline after 5
                }
                putchar('\n');

                break;

            case shell:
                moves = 0;
                compares = 0;
                shell_sort(arr, array_size);
                printf("Shell Sort\n");
                printf("%d elements, %d moves, %d compares", array_size, moves, compares);

                for (int x = 0; x < n_to_print; x++) {
                    if (!(x % 5)) {
                        putchar('\n');
                    }
                    printf("%13" PRIu32, arr[x]); // newline after 5
                }
                putchar('\n');

                break;

            case quick:
                moves = 0;
                compares = 0;
                quick_sort(arr, array_size);
                puts("Quick Sort");
                printf("%d elements, %d moves, %d compares", array_size, moves, compares);

                for (int x = 0; x < n_to_print; x++) {
                    if (!(x % 5)) {
                        putchar('\n');
                    }
                    printf("%13" PRIu32, arr[x]); // newline after 5
                }
                putchar('\n');

                break;

            case heap:
                moves = 0;
                compares = 0;
                heap_sort(arr, array_size);
                printf("Heap Sort\n");
                printf("%d elements, %d moves, %d compares", array_size, moves, compares);

                for (int x = 0; x < n_to_print; x++) {
                    if (!(x % 5)) {
                        putchar('\n');
                    }
                    printf("%13" PRIu32, arr[x]); // newline after 5
                }
                putchar('\n');

                break;
            }
        }

        memcpy(arr, arr2, array_size * sizeof(uint32_t)); // reset the array
    }

    return 0;
}
