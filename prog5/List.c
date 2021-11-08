#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include "List.h"

// -----------------------------
// Instantiates a node and returns ptr to that (newly created) node 
// -----------------------------

node* createList(int n)
{
	node* new = (node*)malloc(sizeof(node));
	new->next = NULL;
	new->prev = NULL;
	new->value = n;
	return new;
}


// -----------------------------
// Returns ptr to node with matching value, else returns NULL
// -----------------------------
node *findList( node *head, int val )
{

	node *ptr;
	//printf("\n\tnow key is:%s\n",ptr->key);
	ptr = head;
	while( ptr != NULL )
	{
		//printf("\n\tWHILE now key is:%s\n",ptr->key);
		if (ptr->value == val){
			return ptr;
		}
		else    ptr = ptr->next;
	}
	
	return( NULL );
	
}

// -----------------------------
// inserts node given a list head 
// -----------------------------
void insertList( node **head, node *new )
{	
	// insert new node as head of list
	if (*head == NULL)
	    {	*head = new;
		(*head)->next = NULL;
		(*head)->prev = NULL;
	    }
	else{	new->next  = *head;
		(*head)->prev = new;
		new->prev  = NULL;
		*head      = new;
	    }
}

// -----------------------------
// Deletes node pointed to by del from the list.
// You can assume that del points to a node in the list.
// -----------------------------
void deleteList( node **head, node *del )
{
	if(*head == del){
		*head = del->next;
	}
	else{
		del->prev->next = del->next;
		if (del->next != NULL) del->next->prev = del->prev;
	}

	free(del);
	
}

// -----------------------------
// Prints value field of each node in the list starting at head.
// -----------------------------
void printList( node *head )
{
	if(head == NULL) return;
	node* cue = head;
	printf("\n\t>>PRINTING LIST>>");
	while (cue != NULL)
	{
		printf("%d\t",cue->value);
		cue = cue->next;
	}
	printf("\n");

}


int getValue(node* x)
{
	return x->value;
}

