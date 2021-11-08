

#include "bf.h"
#include "hash.h"
#include "parser.h"

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "h:f:m"
#define HT_SIZE 1 << 20
#define BF_SIZE 10000
#define WORD    "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+)*"

int main(int argc, char **argv) {
    //loop through getopt
    int opt = 0;
    uint32_t hash_size = HT_SIZE;
    uint32_t filter_size = BF_SIZE;
    bool mtf = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': hash_size = atoi(optarg); break;

        case 'f': filter_size = atoi(optarg); break;

        case 'm': mtf = true; break;
        }
    }

    //creating hash table, bloom filter
    BloomFilter *bf = bf_create(filter_size);
    HashTable *ht = ht_create(hash_size, mtf);

    //creating two linked lists, one for badspeak and one for badspeak, newspeak
    LinkedList *forbidden = ll_create(mtf);
    LinkedList *corrected = ll_create(mtf);

    char oldspeak[1024];
    char newspeak[1024];

    FILE *infile = fopen("badspeak.txt", "r");

    //reading in words from badspeak.txt
    while (fscanf(infile, "%s\n", oldspeak) != EOF) {
        bf_insert(bf, oldspeak);
        ht_insert(ht, oldspeak, NULL);
    }

    fclose(infile);

    FILE *file = fopen("newspeak.txt", "r");

    //reading in words from newspeak.txt
    while (fscanf(file, "%s %s\n", oldspeak, newspeak) != EOF) {
        bf_insert(bf, oldspeak);
        ht_insert(ht, oldspeak, newspeak);
    }

    fclose(file);

    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;
    Node *node = NULL;
    while ((word = next_word(stdin, &re)) != NULL) {

        for (char *c = word; *c; c++) {
            //making all input words lowercase
            *c = tolower(*c);
        }

        //if not in bloom filter, go to next word
        if (!bf_probe(bf, word)) {
            continue;
        }

        //if in bf but not in hash table, go to next word
        if (!(node = ht_lookup(ht, word))) {
            continue;
        }

        if (!node->newspeak) {
            ll_insert(forbidden, word, NULL);
        } else {
            ll_insert(corrected, word, node->newspeak);
        }
    }

    //printing statements
    char reprimand1[] = "Dear Comrade,\n\n\
You have chosen to use degenerate words that may cause hurt\n\
feelings or cause your comrades to think unpleasant thoughts.\n\
This is doubleplus bad. To correct your wrongthink and\n\
preserve community consensus we will be sending you to joycamp\n\
administered by Medellin's Miniluv. Beware of the hippos.\n\n\
Your errors:\n";

    char reprimand2[] = "Dear Comrade,\n\n\
	Submitting your text helps to preserve feelings and prevent\n\
	badthink. Some of the words that you used are not goodspeak.\n\
	The list shows how to turn the oldspeak words into newpseak.\n\n";

    //if at least one bad word was used
    if (ll_length(forbidden) || ll_length(corrected)) {

        if (ll_length(forbidden)) {
            puts(reprimand1);
        } else {
            puts(reprimand2);
        }

        // does nothing if list is empty
        ll_print(forbidden);

        if (ll_length(corrected)) {
            puts("\nThink of these words on your vacation!\n");
            ll_print(corrected);
        }
    }

    bf_delete(&bf);
    ht_delete(&ht);

    ll_delete(&forbidden);
    ll_delete(&corrected);

    clear_words();
    regfree(&re);
    return 0;
}
