
#include "trie.h"

#include "code.h"

#include <stdlib.h>

TrieNode *trie_node_create(uint16_t code) {
    TrieNode *n = (TrieNode *) calloc(1, sizeof(TrieNode));
    if (!n) {
        return NULL;
    }

    n->code = code;
    return n;
}

void trie_node_delete(TrieNode *n) {
    free(n);
}

TrieNode *trie_create(void) {
    return trie_node_create(EMPTY_CODE);
}

void trie_reset(TrieNode *root) {
    for (int i = 0; i < ALPHABET; i++) {
        trie_delete(root->children[i]);
    }
}

void trie_delete(TrieNode *n) {
    if (!n) {
        return;
    }
    for (int i = 0; i < ALPHABET; i++) {
        trie_delete(n->children[i]);
    }
    trie_node_delete(n);
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    return n->children[sym];
}
