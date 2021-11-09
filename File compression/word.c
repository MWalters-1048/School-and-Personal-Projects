
#include "word.h"

#include "code.h"

#include <stdlib.h>
#include <string.h>

Word *word_create(uint8_t *sym, uint32_t len) {
    Word *w = (Word *) calloc(1, sizeof(Word));
    w->len = len;

    w->syms = (uint8_t *) calloc(len, sizeof(uint8_t));
    memcpy(w->syms, sym, len);

    return w;
}

Word *word_append_sym(Word *w, uint8_t sym) {
    Word *wnew = (Word *) malloc(sizeof(Word));
    wnew->len = 1;
    if (w) {
        wnew->len += w->len;
    }

    wnew->syms = (uint8_t *) malloc(wnew->len);
    if (w) {
        memcpy(wnew->syms, w->syms, w->len);
    }
    wnew->syms[wnew->len - 1] = sym;

    return wnew;
}

void word_delete(Word *w) {
    if (w) {
        free(w->syms);
        free(w);
    }
}

WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) calloc(MAX_CODE, sizeof(Word *));
    wt[EMPTY_CODE] = (Word *) calloc(1, sizeof(Word));
    return wt;
}

void wt_delete(WordTable *wt) {
    for (int i = EMPTY_CODE; i < MAX_CODE; i++) {
        word_delete(wt[i]);
    }
    free(wt);
}

void wt_reset(WordTable *wt) {
    for (int i = START_CODE; i < MAX_CODE; i++) {
        word_delete(wt[i]);
        wt[i] = NULL;
    }
}
