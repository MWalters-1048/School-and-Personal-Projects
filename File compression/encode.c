
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

//function for calculating bit length
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
            perror("Failed to open input file");
            return 0;
        }
    }

    FileHeader header = { MAGIC, S_IRWXU };

    if (outfilename) {
        outfile = creat(outfilename, header.protection);
        if (outfile == -1) {
            perror("Failed to open output file");
            return 0;
        }
    }

    if (infile != 0 && outfile != 1) {
        struct stat statbuf;
        fstat(infile, &statbuf);
        fchmod(outfile, statbuf.st_mode);
        // st_mode are permissions of the input
        header.protection = statbuf.st_mode;
    }

    write_header(outfile, &header);

    TrieNode *root = trie_create();
    TrieNode *curr_node = root;

    TrieNode *prev_node = NULL;
    TrieNode *next_node = NULL;
    uint8_t curr_sym = 0, prev_sym = 0;

    uint16_t next_code = START_CODE;

    while (read_sym(infile, &curr_sym)) {
        next_node = trie_step(curr_node, curr_sym);
        if (next_node) {
            prev_node = curr_node;
            curr_node = next_node;
        } else {
            write_pair(outfile, curr_node->code, curr_sym, bit_length(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code++;
        }
        if (next_code == MAX_CODE) {
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }
        prev_sym = curr_sym;
    }
    if (curr_node != root) {
        write_pair(outfile, prev_node->code, prev_sym, bit_length(next_code));
        next_code = (next_code + 1) % MAX_CODE;
    }
    write_pair(outfile, STOP_CODE, 0, bit_length(next_code));
    flush_pairs(outfile);

    trie_delete(root);

    struct stat statbuf;
    if (stat) {
        fstat(outfile, &statbuf);
        unsigned int compressed_size = statbuf.st_size;
        fstat(infile, &statbuf);
        unsigned int uncompressed_size = statbuf.st_size;

        printf("Compressed file size: %u bytes\n", compressed_size);
        printf("Uncompressed file size: %u bytes\n", uncompressed_size);
        printf("Space saving: %.2f%%\n", 100 * (1 - compressed_size / (float) uncompressed_size));
    }

    close(outfile);
    close(infile);

    return 0;
}
