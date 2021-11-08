
#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector));
    if (!bv) {
        return NULL;
    }

    bv->length = length;

    // floor(length/8) + 1 if there's a remaninder
    int bytes = length / 8 + !!(length % 8);

    bv->vector = (uint8_t *) calloc(bytes, sizeof(uint8_t));
    if (!bv->vector) {
        free(bv);
        return NULL;
    }

    return bv;
}

void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

void bv_set_bit(BitVector *bv, uint32_t i) {
    i %= bv->length;
    int byte = bv->vector[i / 8];
    int bit_offset = i % 8;
    int mask = (1 << (7 - bit_offset));
    bv->vector[i / 8] = byte | mask;
    return;
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    i %= bv->length;
    int byte = bv->vector[i / 8];
    int bit_offset = i % 8;
    int mask = ~(1 << (7 - bit_offset));
    bv->vector[i / 8] = byte & mask;
    return;
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    i %= bv->length;
    int byte = bv->vector[i / 8];
    int bit_offset = i % 8;
    int mask = (1 << (7 - bit_offset));
    return !!(byte & mask);
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) {
        printf("%d ", bv_get_bit(bv, i));
    }
}
