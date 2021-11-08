
#include "ll.h"

#include <stdlib.h>
#include <string.h>

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = malloc(sizeof(LinkedList));
    ll->length = 0;
    ll->head = node_create(NULL, NULL);
    ll->tail = node_create(NULL, NULL);
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    ll->mtf = mtf;
    return ll;
}

void ll_delete(LinkedList **ll) {

    if (!ll || !*ll)
        return;

    Node *p = (*ll)->head;
    Node *next;
    while (p) {
        next = p->next;
        node_delete(&p);
        p = next;
    }
    free(*ll);
    *ll = NULL;
    return;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        if (!strcmp(n->oldspeak, oldspeak)) {
            if (ll->mtf && n != ll->head->next) {
                //moving to front
                n->prev->next = n->next;
                n->next->prev = n->prev;

                n->next = ll->head->next;
                n->prev = ll->head;

                ll->head->next->prev = n;
                ll->head->next = n;
            }
            return n;
        }
    }
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    //if it is already inserted
    if (ll_lookup(ll, oldspeak)) {
        return;
    }
    Node *n = node_create(oldspeak, newspeak);
    n->prev = ll->head;
    n->next = ll->head->next;
    ll->head->next->prev = n; //node to insert
    ll->head->next = n;
    ll->length += 1;
}

void ll_print(LinkedList *ll) {
    if (!ll)
        return;
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        node_print(n);
    }
}
