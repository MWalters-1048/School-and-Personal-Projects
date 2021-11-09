#include "List.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Type 1: List is a list with extra node structure

typedef struct NodeObj {
  int data;
  struct NodeObj *next;
} NodeObj;

typedef NodeObj *Node;

typedef struct ListObj {
  Node head;
  int length;
} ListObj;

List newList(void) {
  List l = (List)calloc(1, sizeof(ListObj));
  assert(l != NULL);
  l->length = 0;
  l->head = NULL;

  return l;
}

Node newNode(int data) {
  Node n = (Node)calloc(1, sizeof(NodeObj));
  assert(n != NULL);
  n->data = data;
  n->next = NULL;

  return n;
}

// helper function
// from lab section
void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) {
    Node temp;
    while ((*pL)->head != NULL) {
      temp = (*pL)->head->next;
      freeNode(&(*pL)->head);
      (*pL)->head = temp;
    }

    free(*pL);
    *pL = NULL;
  }
}

int length(List L) {
  if (L == NULL) {
    exit(-1);
  }
  return L->length;
}

int max(List L) {
  if (L == NULL || L->length == 0) {
    exit(-1);
  }

  int m = L->head->data;
  int mi = 0, i = 1;

  Node ptr = L->head->next;
  while (ptr) {
    if (ptr->data > m) {
      m = ptr->data;
      mi = i;
    }
    ptr = ptr->next;
    i++;
  }

  return mi;
}

int find(List L, int i) {
  Node ptr = L->head;
  int index = 0;
  while (ptr) {
    if (ptr->data == i) {
      return index;
    }
    ptr = ptr->next;
    index++;
  }
  return -1;
}

int delElement(List L, int i) {
  if (i < 0 || i >= L->length) {
    exit(-1);
    return -1;
  }

  Node ptr = L->head;
  Node prev = NULL;
  while (i) {
    prev = ptr;
    ptr = ptr->next;
    i--;
  }
  int ret_val = ptr->data;
  if (!prev) {
    L->head = ptr->next;
  } else {
    prev->next = ptr->next;
  }
  free(ptr);
  L->length--;

  return ret_val;
}

void appendList(List L, int i) {
  if (L == NULL) {
    exit(-1);
  }

  Node n = newNode(i);
  if (L->length == 0) {
    L->head = n;
  } else {
    Node ptr = L->head;
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
    ptr->next = n;
  }
  L->length++;
}

void printList(List L) {
  if (L == NULL) {
    exit(-1);
  }

  Node ptr = L->head;
  while (ptr != NULL) {
    printf("%d, ", ptr->data);
    ptr = ptr->next;
  }
  printf("\n");
}

// extra function to get value at index
int get_val(List L, int index) {
  if (!L || index < 0 || index >= L->length) {
    exit(-1);
  }

  Node p = L->head;
  while (index) {
    p = p->next;
    index--;
  }

  return p->data;
}
