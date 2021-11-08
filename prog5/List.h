// -------------------------------
// List ADT for doubly linked list
//
// -------------------------------

typedef struct node {
        int value;
        struct node     *next;
        struct node     *prev;
        } node;              

// -----------------------------
// Function headers
//
// -----------------------------

node* createList(int n);
node	*findList ( node  *head, int val );

void	insertList( node **head, node *new );

void	deleteList( node **head, node *del );
void	printList ( node  *head );

// getter function to return value of a node

int getValue(node* x);

