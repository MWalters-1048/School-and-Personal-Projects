// implentation of the bit matrix ADT
// define bit matrix struct here

#include "bm.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    uint8_t **mat;
};

// helper function from Eugene lab section
uint32_t bytes(uint32_t bits) {
    if (bits % 8 == 0) {
        return (bits / 8);
    } else {
        return (bits / 8) + 1;
    }
}

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    if (!m) {
        return NULL;
    }
    m->rows = rows;
    m->cols = cols;

    m->mat = (uint8_t **) calloc(rows, sizeof(uint8_t *));
    if (!m->mat)
        return NULL;
    for (uint32_t r = 0; r < rows; r++) {
        m->mat[r] = (uint8_t *) calloc(bytes(cols), sizeof(uint8_t));
        if (!m->mat[r])
            return NULL;
    }

    return m;
}

void bm_delete(BitMatrix **mat) {
    BitMatrix *m = *mat;
    for (uint32_t r = 0; r < m->rows; r++) {
        free(m->mat[r]);
    }
    free(m->mat);
    free(m);

    *mat = NULL;
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

// 1111 1001
// set, clear, and get and inspired by eugene lab section
void bm_set_bit(BitMatrix *m, uint32_t row, uint32_t col) {
    int byte = m->mat[row][col / 8];
    col = col % 8;
    int mask = 1 << (7 - col);
    m->mat[row][col / 8] = byte | mask;
}

void bm_clr_bit(BitMatrix *m, uint32_t row, uint32_t col) {
    int byte = m->mat[row][col / 8];
    col = col % 8;
    int mask = ~(1 << (7 - col));
    m->mat[row][col / 8] = byte & mask;
    return;
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t row, uint32_t col) {
    int byte = m->mat[row][col / 8];
    col = col % 8;
    int mask = 1 << (7 - col);
    return !!(byte & mask); // !! takes non-zero to 1 zero stays 0
}

void bm_print(BitMatrix *m) {
    puts("=====");
    for (uint32_t i = 0; i < m->rows; i++) {
        for (uint32_t j = 0; j < m->cols; j++) {
            printf("%d ", bm_get_bit(m, i, j));
        }
        putchar('\n');
    }
    puts("=====");
}
