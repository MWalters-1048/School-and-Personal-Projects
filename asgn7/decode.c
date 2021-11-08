#include "code.h"
#include "io.h"
#include "trie.h"
#include "word.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "vi:o:"

// log function to calculate bit_length
int ilog2(int n) {
    int r = 0;
    while (n >>= 1)
        ++r;
    return r;
}

int bit_length(uint16_t code) {
    return (!code) ? 1 : ilog2(code) + 1;
}

int main(int argc, char **argv) {
    int opt = 0;
    bool stat = false;
    int infile = 0;
    int outfile = 1;

    char *infilename = NULL;
    char *outfilename = NULL;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'v': stat = true; break;

        case 'i': infilename = optarg; break;

        case 'o': outfilename = optarg; break;
        }
    }
    if (infilename) {
        infile = open(infilename, O_RDONLY);
        if (infile == -1) {
            fprintf(stderr, "Failed to open infile\n");
            return 1;
        }
    }

    FileHeader header;

    read_header(infile, &header);

    if (outfilename) {
        outfile = creat(outfilename, header.protection);
        if (outfile == -1) {
            fprintf(stderr, "failed to open infile\n");
            return 1;
        }
    }

    if (infile != 0 && outfile != 1) {
        //create a stat strcut. get infile stats. copy over the permissions
        struct stat statbuf;
        fstat(infile, &statbuf);

        fchmod(outfile, statbuf.st_mode);
        // st_mode are permissions of the input
        header.protection = statbuf.st_mode;
    }

    WordTable *table = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;

    while (read_pair(infile, &curr_code, &curr_sym, bit_length(next_code))) {
        table[next_code] = word_append_sym(table[curr_code], curr_sym);
        write_word(outfile, table[next_code]);
        next_code++;
        if (next_code == MAX_CODE) {

            wt_reset(table);
            next_code = START_CODE;
        }
    }
    flush_words(outfile);

    wt_delete(table);

    struct stat statbuf;

    if (stat) {
        fstat(outfile, &statbuf);
        unsigned int uncompressed_size = statbuf.st_size;
        fstat(infile, &statbuf);
        unsigned int compressed_size = statbuf.st_size;

        printf("Compressed file size: %u bytes\n", compressed_size);
        printf("Uncompressed file size: %u bytes\n", uncompressed_size);
        printf("Space saving: %.2f%%\n", 100 * (1 - compressed_size / (float) uncompressed_size));
    }

    close(outfile);
    close(infile);

    return 0;
}
