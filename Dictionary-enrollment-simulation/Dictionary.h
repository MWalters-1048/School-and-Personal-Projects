// -------------------------------
// Dictionary ADT:
// 
// -------------------------------

#include "HashTable.h"


typedef struct {
	char		key[5];		// key for dictionary element
	void*		value;		// generic pointer to value of dictionary element
	}		element;		// key:value pair of dictionary elements


typedef struct {
	int		slots;				// total number of slots in hash table
	int		size;				// number of elements currently in dictionary
	node_t		*hash_table;	// hash_table is array of  node_t
	}		dictionary;			// dictionary is maintained as a hash table.


// -------------------------------
// Function headers
// -------------------------------

// -------------------------------
// create( *D, n ) -- creates a dictionary with n slots
// -------------------------------
void create( dictionary* D, int n );


// -------------------------------
// insert( *D, *e ) -- inserts element e->key:e->value into the dictionary.
// -------------------------------
int insert( dictionary* D, element *e );


// -------------------------------
// delete( *D, *key ) -- deletes element with key (*key) from the dictionary.
// -------------------------------
int delete( dictionary* D, char *key );


// -------------------------------
// find( *D, *k ) -- returns pointer to node in dictionary whose key is k
// -------------------------------

node_t *find( dictionary* D, char *k );


// -------------------------------
// print( dictionary* D ) -- prints the dictionary.
// -------------------------------
void print( dictionary* D );
