
#include "hamming.h"

#include "bm.h"

#include <stdio.h>

static BitMatrix *G;
static BitMatrix *H;

ham_rc ham_init() {
    G = bm_create(4, 8);
    //if it fails
    if (!G) {
        return HAM_ERR;
    }

    //left side of G matrix
    bm_set_bit(G, 0, 0);
    bm_set_bit(G, 1, 1);
    bm_set_bit(G, 2, 2);
    bm_set_bit(G, 3, 3);

    //right side of G matrix
    bm_set_bit(G, 0, 5);
    bm_set_bit(G, 0, 6);
    bm_set_bit(G, 0, 7);

    bm_set_bit(G, 1, 4);
    bm_set_bit(G, 1, 6);
    bm_set_bit(G, 1, 7);

    bm_set_bit(G, 2, 4);
    bm_set_bit(G, 2, 5);
    bm_set_bit(G, 2, 7);

    bm_set_bit(G, 3, 4);
    bm_set_bit(G, 3, 5);
    bm_set_bit(G, 3, 6);

    // Transpose of H matrix
    H = bm_create(8, 4);
    // if it fails
    if (!H) {
        return HAM_ERR;
    }

    bm_set_bit(H, 0, 1);
    bm_set_bit(H, 0, 2);
    bm_set_bit(H, 0, 3);

    bm_set_bit(H, 1, 0);
    bm_set_bit(H, 1, 2);
    bm_set_bit(H, 1, 3);

    bm_set_bit(H, 2, 0);
    bm_set_bit(H, 2, 1);
    bm_set_bit(H, 2, 3);

    bm_set_bit(H, 3, 0);
    bm_set_bit(H, 3, 1);
    bm_set_bit(H, 3, 2);

    bm_set_bit(H, 4, 0);
    bm_set_bit(H, 5, 1);
    bm_set_bit(H, 6, 2);
    bm_set_bit(H, 7, 3);

    //bm_print(G);
    //bm_print(H);
    return HAM_OK;
}

void ham_destroy() {
    bm_delete(&G);
    bm_delete(&H);
}

ham_rc ham_encode(uint8_t data, uint8_t *code) {
    if (!G || !H || !code) {
        return HAM_ERR;
    }

    // nested loop to multiply matrices
    uint8_t c, g, sum, ret = 0;
    for (int i = 0; i < (int) bm_cols(G); i++) {
        sum = 0;
        for (int j = 0; j < 4; ++j) {
            //isolates bit
            c = (data >> j) & 0x1;
            g = bm_get_bit(G, j, i);
            sum ^= c & g;
        }
        ret |= sum << i;
    }
    *code = ret;
    return HAM_OK;
}

ham_rc ham_decode(uint8_t code, uint8_t *data) {
    if (!G || !H || !data) {
        return HAM_ERR;
    }

    // create an arrray for my look-up table
    int lookup[16] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2, 5, 1,
        0, HAM_ERR };

    // loop to multiply matrices M and H
    uint8_t c, h, sum, ret = 0;
    for (int i = 0; i < (int) bm_cols(H); i++) {
        sum = 0;
        for (int j = 0; j < (int) bm_rows(H); ++j) {
            c = (code >> j) & 0x1;
            h = bm_get_bit(H, j, i);
            sum ^= c & h;
        }
        ret |= sum << i;
    }

    *data = code & 0xF;

    if (!ret) {
        return HAM_OK;
    }

    int bit = lookup[ret];

    uint8_t tmp = 0;
    if (bit == HAM_ERR) {

        return HAM_ERR;
    } else {
        tmp = (code >> bit) & 0x1;
        tmp = !tmp;
        if (!tmp) {
            code &= ~(1 << bit);
        } else {
            code |= 1 << bit;
        }
        *data = code & 0xF;
        return HAM_ERR_OK;
    }
}
