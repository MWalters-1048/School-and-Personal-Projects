#include "hash.h"

#include "speck.h"

#include <stdlib.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x85ae998311115ae3;
        ht->salt[1] = 0xb6fac2ae33a40089;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {

    HashTable *h = *ht;
    for (uint32_t i = 0; i < h->size; i++) {
        ll_delete(&h->lists[i]);
    }
    free(h->lists);
    free(h);
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {

    uint32_t index = hash(ht->salt, oldspeak);
    //% with size to no go out of bounds
    index %= ht->size;
    if (!ht->lists[index]) {
        return NULL;
    }

    return ll_lookup(ht->lists[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak);
    //% with size to not go out of bounds
    index %= ht->size;

    if (!ht->lists[index]) {
        ht->lists[index] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[index], oldspeak, newspeak);
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        ll_print(ht->lists[i]);
    }
}
