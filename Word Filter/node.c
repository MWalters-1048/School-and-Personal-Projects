

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *mystrdup(const char *str) {
    if (!str)
        return NULL;

    size_t len = strlen(str);
    char *temp = (char *) calloc(len + 1, sizeof(char));
    if (!temp) {
        return NULL;
    }

    return (char *) memcpy(temp, str, len);
}

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (!n) {
        return NULL;
    }

    n->oldspeak = mystrdup(oldspeak);
    n->newspeak = mystrdup(newspeak);

    n->next = NULL;
    n->prev = NULL;
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free((*n)->oldspeak);
        free((*n)->newspeak);
        free(*n);
        *n = NULL;
    }
    return;
}

void node_print(Node *n) {
    if (!n) {
        return;
    }

    if (!n->newspeak) {
        printf("%s\n", n->oldspeak);
    } else {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
}
