
#include "universe.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROW     0
#define DELAY   50000
#define OPTIONS "tsn:i:o:"

int main(int argc, char **argv) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int generations = 100;
    bool toroidal = false;
    bool silence = false;

    // looping through command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': toroidal = true; break;

        case 's': silence = true; break;

        case 'n':
            generations = atoi(optarg);
            if (generations < 0) {
                fprintf(stderr, "invalid number of generations.\n");
                return 1;
            }
            break;

        case 'i':
            infile = fopen(optarg, "r");
            // error if file is NULL
            if (infile == NULL) {
                fprintf(stderr, "infile is NULL.\n");
                return 1;
            }
            break;

        case 'o':
            outfile = fopen(optarg, "w");
            // error if file is NULL
            if (outfile == NULL) {
                fprintf(stderr, "outfile is NULL.\n");
                return 1;
            }
            break;
        }
    }

    int rows = 0;
    int cols = 0;

    fscanf(infile, "%d %d\n", &rows, &cols);

    // creating universe a and b
    Universe *a = uv_create(rows, cols, toroidal);
    Universe *b = uv_create(rows, cols, toroidal);

    uv_populate(a, infile);

    //initscr();
    //curs_set(FALSE);

    int count = 0;

    for (int i = 0; i < generations; i++) {
        if (silence == false) {
            //clear();
            //display universe a
            //refresh();
            //usleep(DELAY);
        }

        // looping through the universe matrix and following conditions to change state of cell
        for (int x = 0; x < uv_rows(a); x++) {
            for (int y = 0; y < uv_cols(a); y++) {
                count = uv_census(a, x, y);
                if (count == 2 || count == 3) {
                    uv_live_cell(b, x, y);
                } else if (uv_get_cell(a, x, y) == false && count == 3) {
                    uv_live_cell(b, x, y);
                } else {
                    uv_dead_cell(b, x, y);
                }
            }
        }
        // swapping universes
        Universe *temp = a;
        a = b;
        b = temp;
    }

    //endwin();
    uv_print(a, outfile);
    uv_delete(a);
    uv_delete(b);
    fclose(infile);
    fclose(outfile);
    return 0;
}
