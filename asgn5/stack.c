//implementation of stack ADT

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

Stack *stack_create(void) {
    Stack *s = (Stack *) calloc(1, sizeof(Stack));
    if (!s) {
        return NULL;
    }

    s->top = 0;
    s->capacity = MIN_CAPACITY;

    s->items = (int64_t *) calloc(MIN_CAPACITY, sizeof(int64_t));
    if (!s->items) {
        free(s);
        return NULL;
    }

    return s;
}

void stack_delete(Stack **s) {
    free((*s)->items);
    free(*s);

    *s = NULL;
}

bool stack_empty(Stack *s) {
    return s->top == 0;
}

bool stack_push(Stack *s, int64_t x) {
    int64_t *tmp;
    if (s->top == s->capacity) {
        tmp = realloc(s->items, s->capacity * 2 * sizeof(int64_t));
        if (!tmp) {
            return false;
        }
        s->items = tmp;
        s->capacity *= 2;
    }

    s->items[s->top] = x;
    s->top++; // point to next empty slot
    return true;
}

bool stack_pop(Stack *s, int64_t *x) {
    //check is stack is empty, return false
    if (!s->top) {
        return false;
    }

    s->top--;
    *x = s->items[s->top];
    return true;
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; ++i) {
        printf("%ld ", s->items[i]);
    }
    putchar('\n');
}
