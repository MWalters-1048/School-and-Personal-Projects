// -------------------------------
// List ADT for doubly linked list
//
// -------------------------------

typedef struct node {
        char            key[5];         // key of an element struct
        void            *value;         // value field of element struct
        struct node     *next;
        struct node     *prev;
        } node_t;                       // a node in a chained hash

// -----------------------------
// Function headers
//
// -----------------------------

node_t	*findList ( node_t  *head, char *key );
void	insertList( node_t **head, node_t *new );
void	deleteList( node_t **head, node_t *del );
void	printList ( node_t  *head );

