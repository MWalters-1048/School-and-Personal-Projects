#include "bf.h"

#include "speck.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = 0x02d232593fbe42ff;
        bf->primary[1] = 0x3775cfbf0794f152;

        bf->secondary[0] = 0xc1706bc17ececc04;
        bf->secondary[1] = 0xe9820aa4d2b8261a;

        bf->tertiary[0] = 0xd37b01df0ae8f8d0;
        bf->tertiary[1] = 0x911d454886ca7cf7;

        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    bv_delete(&((*bf)->filter));
    free(*bf);
    *bf = NULL;
}

uint32_t bf_length(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    //hash at the three different salts and set the bit at the index

    uint32_t i1 = hash(bf->primary, oldspeak);
    bv_set_bit(bf->filter, i1);

    uint32_t i2 = hash(bf->secondary, oldspeak);
    bv_set_bit(bf->filter, i2);

    uint32_t i3 = hash(bf->tertiary, oldspeak);
    bv_set_bit(bf->filter, i3);
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    //hashes with three salts to get index
    //checks if each bit is set
    //0 & with anything is 0 so if anyone is not set then it aint in there
    uint32_t i1 = hash(bf->primary, oldspeak);
    int result = bv_get_bit(bf->filter, i1);

    uint32_t i2 = hash(bf->secondary, oldspeak);
    result &= bv_get_bit(bf->filter, i2);

    uint32_t i3 = hash(bf->tertiary, oldspeak);
    result &= bv_get_bit(bf->filter, i3);

    return result;
}

void bf_print(BloomFilter *bf) {

    bv_print(bf->filter);
}
