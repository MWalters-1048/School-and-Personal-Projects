//implementation of set ADT
//most are 1-2 lines
#include "set.h"

Set set_empty(void) {
    return 0;
}

bool set_member(Set s, uint8_t x) {
    return s & (1 << x);
}

Set set_insert(Set s, uint8_t x) {
    return s | (1 << x);
}

Set set_remove(Set s, uint8_t x) {
    return s & ~(1 << x);
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_union(Set s, Set t) {
    return s | t;
}

Set set_complement(Set s) {
    return ~s;
}

Set set_difference(Set s, Set t) {
    return s & ~t;
}
