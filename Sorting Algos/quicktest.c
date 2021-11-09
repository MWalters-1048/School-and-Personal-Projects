
#include "hamming.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Returns the lower nibble of val
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

// Returns the upper nibble of val
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

// Packs two nibbles into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

void print_byte(uint8_t byte) {
    for (int i = 0; i < 8; ++i) {
        printf("%d ", (byte >> i) & 0x1);
    }
}

int main() {

    ham_init();
    uint8_t byte, hinibble, lonibble, locode, hicode;
    for (int i = 0; i < 16; i++) {

        lonibble = lower_nibble(i);

        ham_encode(lonibble, &locode);

        printf("%d = ", i);
        print_byte(locode);
        putchar('\n');
    }

    ham_destroy();

    return 0;
}
