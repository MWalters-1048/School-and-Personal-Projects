// -------------------------------
// Dictionary ADT:
//
// -------------------------------

#include <stdlib.h>		// for built-in malloc that returns void *
#include "Dictionary.h"
#include <string.h>
#include <stdio.h>
// -------------------------------
// TODO: implement create
// create( *D, n ) -- creates a dictionary with n slots
// Initializes slots to n, and size to 0.
// -------------------------------

void create(dictionary *D, int n) {

	// initialize the 'slots' and 'size' field
	D->slots = n;
	D->size = 0;

	// allocate memory for 'n' node_t structs and assignt to 'hash_table' field
	D->hash_table = calloc(n, sizeof(node_t));	


}

// -------------------------------
// TODO: implement insert
// insert( *D, *e ) -- inserts element e->key:e->value into the dictionary.
// First, make sure that e->key does not exist in *D yet.
// If it does, return an error code of -1.
// Otherwise, update the size of *D, and return 0.
// -------------------------------

int insert(dictionary* D, element* e) {
	
	// check if element's key already in dictionary
	if (find(D, e->key)) {
		return -1;
	}

	// if not:

	// instantiate a new node, intialize everything to 0/NULL
	node_t *node = calloc(1, sizeof(node_t));
	
	// set the 'key' and 'value' fields of the newly instantiated node
	// these come from 'key' and 'value' fields of element
    // HINT: can use memcpy to copy element's key to node's key field
	memcpy(node->key, e->key, 5);
	node->value = e->value;

    // get the index of element in the dictionary
	int hash_idx = hash(node->key, D->slots);

	
	// using the index, get the node/head of the list corresp. to that index
	// add the newly created node to the list
	// NOTE: this follows the same logic of adding a node to list
	// but do NOT use insertList from List.c
	//insertList(&D->hashtable[hash_idx]->next, node);


	// copy pasted with modifications from insertList 
	node_t** head = &D->hash_table[hash_idx].next;
	// insert new node as head of list
	if (*head == NULL) {
		*head = node;
	} else {
		node->next = *head;
		(*head)->prev = node;
		*head = node;
	}

	D->size++;
	return 0;
}



// -------------------------------
// TODO: implement delete
// delete( *D, *key ) -- deletes element with key (*key) from the dictionary.
// If *key does not exist in *D, return an error code of -1.
// Update the size of *D, and return 0.
// -------------------------------

int delete(dictionary* D, char* key)
{

	node_t* del = NULL;
	// check if element's key already in dictionary
	if (!(del = find(D, key))) {
		return -1;
	}

		
	// if key exists, navigate to the node that has such key
	// remove the node from the list
	// NOTE: again, this is same logic as in deleting a node
	// but do NOT use delete method from List.c

    // get the index of element in the dictionary
	int hash_idx = hash(key, D->slots);
	node_t** head = &D->hash_table[hash_idx].next;

	if (del->next) {
		del->next->prev = del->prev;
	}

	if (del->prev) {
		del->prev->next = del->next;
	}

	if (*head == del) {
		*head = del->next;
	}

	free(del);

	D->size--;

	return 0;
}



// -------------------------------
// TODO: implement find
// find( D, k ) -- returns pointer to node whose key is *k from dictionary *D.
// If *k is not found in *D, then return NULL.
// -------------------------------

node_t* find(dictionary* D, char* k) {

	// hash key to get index and then loop over the list at that index
	// to find node with same key
	// NOTE: you can use the findList method from List.c but need to
	// distinguish between the case when it returns the node with key
	// or just the sentinel head of the list at that index of the dict
	int hash_idx = hash(k, D->slots);
	
	return findList(D->hash_table[hash_idx].next, k);
	
}


// -------------------------------
// TODO: implement print
// print( dictionary *D ) -- prints the dictionary.
// Specifically, it looks at the non-empty slots of the hash table,
// and prints the key field of each node in the list.
// -------------------------------

void print(dictionary* D)
{
	node_t* p;
	for (int i = 0; i < D->slots; i++) {
		p = D->hash_table[i].next;
		if (p) {
			printf("%d: ", i);
			while (p) {
				printf("%s ", p->key);
				p = p->next;
			}
			putchar('\n');
		}
   	}
}
