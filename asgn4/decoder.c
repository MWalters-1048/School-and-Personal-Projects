
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

    uint8_t pair[2];
    ;
    uint8_t lonibble, hinibble;

    int num_bytes = 0;
    int uncorrected = 0;
    int corrected = 0;
    int ret;

    while (fread(pair, 2, 1, infile) == 1) {
        ret = ham_decode(pair[0], &lonibble);
        if (ret == HAM_ERR)
            uncorrected++;
        else if (ret == HAM_ERR_OK)
            corrected++;
        ret = ham_decode(pair[1], &hinibble);
        if (ret == HAM_ERR)
            uncorrected++;
        else if (ret == HAM_ERR_OK)
            corrected++;

        fputc(pack_byte(hinibble, lonibble), outfile);

        num_bytes += 2;
    }

    float e = uncorrected / (float) num_bytes;
    //printing with stderr
    fprintf(stderr, "Total bytes processed: %d\n", num_bytes);
    fprintf(stderr, "Uncorrected errors: %d\n", uncorrected);
    fprintf(stderr, "Corrected errors: %d\n", corrected);
    fprintf(stderr, "Error rate: %f\n", e);

    ham_destroy();
    // file permissions from eugene lab section
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
