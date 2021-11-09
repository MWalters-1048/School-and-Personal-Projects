#include "universe.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Universe {
    int rows;
    int cols;
    bool **grid;
    bool toroidal;
};

// credit to Eugene lab section 1/26/21
struct Universe *uv_create(int rows, int cols, bool toroidal) {
    Universe *u = (Universe *) calloc(1, sizeof(Universe));
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    for (int r = 0; r < rows; r = r + 1) {
        u->grid[r] = (bool *) calloc(cols, sizeof(bool));
    }
    return u;
}

// credit to Eugene lab section 1/26/21
void uv_delete(struct Universe *u) {
    for (int r = 0; r < u->rows; r = r + 1) {
        free(u->grid[r]);
    }

    free(u->grid);
    free(u);
    return;
}

int uv_rows(struct Universe *u) {
    return u->rows;
}

int uv_cols(struct Universe *u) {
    return u->cols;
}

void uv_live_cell(struct Universe *u, int r, int c) {
    // checking bounds
    if (r >= u->rows || c >= u->cols) {
        return;
    } else if (r < 0 || c < 0) {
        return;
    } else {
        u->grid[r][c] = true;
        return;
    }
}

void uv_dead_cell(struct Universe *u, int r, int c) {
    //checking bounds
    if (r >= u->rows || c >= u->cols) {
        return;
    } else if (r < 0 || c < 0) {
        return;
    } else {
        u->grid[r][c] = false;
        return;
    }
}

bool uv_get_cell(struct Universe *u, int r, int c) {
    //checking bounds
    if (r >= u->rows || c >= u->cols) {
        return false;
    } else if (r < 0 || c < 0) {
        return false;
    } else {
        bool ret = u->grid[r][c];
        return ret;
    }
}

bool uv_populate(struct Universe *u, FILE *infile) {

    int r = 0;
    int c = 0;
    while (fscanf(infile, "%d %d\n", &r, &c) != EOF) {
        if (r >= u->rows || c >= u->cols) {
            fprintf(stderr, "out of bounds\n");
            return false;
        } else if (r < 0 || c < 0) {
            fprintf(stderr, "out of bounds\n");
            return false;
        } else {
            u->grid[r][c] = true;
        }
    }
    return true;
}

int uv_census(struct Universe *u, int r, int c) {
    // checking state of each cell next to specified cell
    int counter = 0;
    if (u->toroidal == true) {

        if (uv_get_cell(u, ((-1 + r) % r), ((-1 + c) % c)) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, (-1 + r) % r, (c) % c) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, (-1 + r) % r, (1 + c) % c) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, (r) % r, (-1 + c) % c) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, (r) % r, (1 + c) % c) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, (1 + r) % r, (-1 + c) % c) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, (1 + r) % r, (c) % c) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, (1 + r) % r, (1 + c) % c) == true) {
            counter = counter + 1;
        }
    } else {

        if (uv_get_cell(u, r - 1, c - 1) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, r - 1, c) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, r - 1, c + 1) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, r, c - 1) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, r + 1, c + 1) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, r + 1, c - 1) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, r + 1, c) == true) {
            counter = counter + 1;
        }
        if (uv_get_cell(u, r + 1, c + 1) == true) {
            counter = counter + 1;
        }
    }
    return counter;
}

void uv_print(struct Universe *u, FILE *outfile) {
    int x = 0;
    int y = 0;

    while (y < u->cols) {
        for (x = 0; x < u->rows; x++) {
            if (u->grid[x][y] == true) {
                fprintf(outfile, "o");
            }
            if (u->grid[x][y] == false) {
                fprintf(outfile, ".");
            }
        }
        printf("\n");
        y = y + 1;
    }
    return;
}
