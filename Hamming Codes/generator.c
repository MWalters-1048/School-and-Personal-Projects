
#include "hamming.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// helper functions from lab document
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

#define OPTIONS "i:o:"

int main(int argc, char **argv) {
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;

    // looping through command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;

        case 'o': outfile = fopen(optarg, "w"); break;
        }
    }

    ham_init();

    int byte;
    uint8_t hinibble, lonibble, locode, hicode;
    //looping through file and encoding
    while ((byte = fgetc(infile)) != EOF) {
        hinibble = upper_nibble(byte);
        lonibble = lower_nibble(byte);

        ham_encode(lonibble, &locode);
        ham_encode(hinibble, &hicode);

        fputc(locode, outfile);
        fputc(hicode, outfile);
    }

    ham_destroy();
    // credit to eugene lab section for copying permissions

    if (infile != stdin && outfile != stdout) {
        //create a stat strcut. get infile stats. copy over the permissions
        struct stat statbuf;
        fstat(fileno(infile), &statbuf);
        fchmod(fileno(outfile), statbuf.st_mode);
        // st_mode are permissions of the input
    }

    if (infile != stdin)
        fclose(infile);
    if (outfile != stdout)
        fclose(outfile);

    return 0;
}
