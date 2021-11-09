
#include "io.h"

#include "code.h"
#include "endian.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int cur_sym;
static uint8_t symbuf[BLOCK];

static int cur_bit;
static uint8_t pairbuf[BLOCK];

uint64_t total_syms;

//inspired by Sahiti lab section
int read_bytes(int infile, uint8_t *buf, int to_read) {
    int bytes_read = 0;
    int total_bytes_read = 0;

    while (to_read) {
        bytes_read = read(infile, buf + total_bytes_read, to_read);
        if (bytes_read == -1) {
            fprintf(stderr, "failed to read\n");
            return 1;

        } else if (!bytes_read) {
            break;
        }
        to_read -= bytes_read;
        total_bytes_read += bytes_read;
    }
    return total_bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int bytes_written = 0;
    int total_bytes_written = 0;

    while (to_write) {
        bytes_written = write(outfile, buf + total_bytes_written, to_write);
        if (bytes_written == -1) {
            fprintf(stderr, "Failed to write\n");
            return 1;
        } else if (!bytes_written) {
            break;
        }
        to_write -= bytes_written;
        total_bytes_written += bytes_written;
    }
    return total_bytes_written;
}

void read_header(int infile, FileHeader *header) {
    read_bytes(infile, (uint8_t *) header, sizeof(FileHeader));
    if (big_endian()) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    if (header->magic != MAGIC) {
        fprintf(stderr, "Invalid Magic number, exiting\n");
        exit(0);
    }
}

void write_header(int outfile, FileHeader *header) {
    if (big_endian()) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }

    write_bytes(outfile, (uint8_t *) header, sizeof(FileHeader));
}

bool read_sym(int infile, uint8_t *sym) {
    int bytes_read;
    static int end;
    if (cur_sym == end) {
        if (!(bytes_read = read_bytes(infile, symbuf, BLOCK))) {
            return false;
        }
        end = bytes_read;
        cur_sym = 0;
    }
    *sym = symbuf[cur_sym];
    cur_sym++;

    return true;
}

// helper functions for write_pair
static void bv_set_bit(uint8_t *bv, uint32_t i) {
    int byte = bv[i / 8];
    int bit_offset = i % 8;
    int mask = (1 << (7 - bit_offset));
    bv[i / 8] = byte | mask;
    return;
}

static void bv_clr_bit(uint8_t *bv, uint32_t i) {
    int byte = bv[i / 8];
    int bit_offset = i % 8;
    int mask = ~(1 << (7 - bit_offset));
    bv[i / 8] = byte & mask;
    return;
}

static void swap_bytes(int last_byte) {
    int num_bytes = cur_bit / 8;
    if (last_byte) {
        num_bytes += !!(cur_bit % 8);
    }
    uint8_t byte_in, byte_out;
    for (int i = 0; i < num_bytes; ++i) {
        byte_out = 0;
        byte_in = pairbuf[i];
        for (int j = 0; j < 8; j++) {
            byte_out |= (byte_in & 0x1) << (7 - j);
            byte_in >>= 1;
        }
        pairbuf[i] = byte_out;
    }
}

// inspired by Eugene lab section
void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {

    if (big_endian()) {
        code = swap16(code);
    }
    int bytes_written;
    uint8_t last_byte = 0;
    if (cur_bit + bitlen + 8 > BLOCK * 8) {
        swap_bytes(0);
        bytes_written = write_bytes(outfile, pairbuf, cur_bit / 8);

        if (cur_bit % 8) {
            last_byte = pairbuf[cur_bit / 8];
            memset(pairbuf, 0, BLOCK);
            pairbuf[0] = last_byte;
            cur_bit = cur_bit % 8;
        } else {
            memset(pairbuf, 0, BLOCK);
            cur_bit = 0;
        }
    }

    for (int i = 0; i < bitlen; i++) {
        if ((code >> i) & 0x1) {
            bv_set_bit(pairbuf, cur_bit + i);
        } else {
            bv_clr_bit(pairbuf, cur_bit + i);
        }
    }
    cur_bit += bitlen;

    for (int i = 0; i < 8; i++) {
        if ((sym >> i) & 0x1) {
            bv_set_bit(pairbuf, cur_bit + i);
        } else {
            bv_clr_bit(pairbuf, cur_bit + i);
        }
    }
    cur_bit += 8;
}

void flush_pairs(int outfile) {
    //if there are still bits in the buffer, write_bytes
    swap_bytes(1);
    write_bytes(outfile, pairbuf, cur_bit / 8 + !!(cur_bit % 8));
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {

    static int end = 0;
    uint8_t byte;
    if (cur_bit + bitlen + 8 > end) {
        int j = 0;
        if (cur_bit % 8) {
            byte = cur_bit / 8;
            // save all bytes that haven't completely been read
            for (int i = byte; i < BLOCK; i++, j++) {
                pairbuf[j] = pairbuf[i];
            }
            // read enough to fill up buffer
            end = read_bytes(infile, &pairbuf[j], BLOCK - j);

            // start on first bit of byte not read
            cur_bit %= 8;
        } else {
            end = read_bytes(infile, pairbuf, BLOCK);
            cur_bit = 0;
        }

        if (!end) {
            return false;
        }
        // add in bytes left from end if necessary
        end += j;
        // multiply by bits per byte
        end *= 8;
    }

    *code = 0;
    int which = cur_bit / 8;
    byte = pairbuf[which];
    int bit = cur_bit % 8;
    for (int i = 0; i < bitlen; i++) {

        *code |= ((byte >> bit) & 0x1) << i;
        bit++;
        if (bit == 8) {
            byte = pairbuf[++which];
            bit = 0;
        }
    }
    cur_bit += bitlen;

    *sym = 0;
    which = cur_bit / 8;
    byte = pairbuf[which];
    bit = cur_bit % 8;
    for (int i = 0; i < 8; i++) {
        *sym |= ((byte >> bit) & 0x1) << i;
        bit++;
        if (bit == 8) {
            byte = pairbuf[++which];
            bit = 0;
        }
    }
    cur_bit += 8;

    return *code != STOP_CODE;
}

void write_word(int outfile, Word *w) {
    for (uint32_t i = 0; i < w->len; i++) {
        symbuf[cur_sym++] = w->syms[i];
        total_syms++;

        if (cur_sym == BLOCK) {
            write_bytes(outfile, symbuf, BLOCK);
            cur_sym = 0;
        }
    }
}

void flush_words(int outfile) {
    if (cur_sym) {
        write_bytes(outfile, symbuf, cur_sym);
    }
}
