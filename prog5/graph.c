#include<stdlib.h>
#include<stdio.h>
#include"List.h"
#include"graph.h"

/* TODO: implement graph constructor
Instantiate a graph given the number of vertices
There are no edges at instantiation
*/

graph CreateGraph(int num) {

	graph g = calloc(1, sizeof(*g)); //maybe g inside

	g->matrix = (int**)calloc(num, sizeof(int*));
	
	for (int i = 0; i < num; i++) {
		g->matrix[i] = (int*)calloc(num, sizeof(int));
	}

	g->n = num;

	return g;

}




/* TODO: implement graph destructor
destruct graph and free allocated memory as appropriate
*/

void destructGraph(graph g) {
	for (int i = 0; i < g->n; i++) {
		free(g->matrix[i]);
	}

	free(g->matrix);
	free(g);
	return;
}


// TODO: implement addEdge function
void addEdge(graph g, int i, int j) {
	g->matrix[i][j] = 1;
}



// TODO: implement removeEdge function
void removeEdge(graph g, int i, int j) {
	g->matrix[i][j] = 0;
}


// TODO: implement hasEdge function
int hasEdge(graph g, int i, int j) {
	return g->matrix[i][j];
}




// TODO: implement outEdges function
//maybe change g->n/2 to g->n??
void outEdges(graph g, int i, node** list) {
	for (int n = 0; n < g->n; n++) {
		if (g->matrix[i][n]) {
			node* new = (node*)malloc(sizeof(node));
			new->value = n;
			insertList(list, new); 
		}
	}
return;
}


// TODO: implement inEdges function
void inEdges(graph g, int j, node** list) {
        for (int n = 0; n < g->n; n++) {
                if (g->matrix[n][j]) {
                        node* new = (node*)malloc(sizeof(node));
                        new->value = n;
                        insertList(list, new); 
                }
        }
return;
}




// TODO: implement getNumVer
int getNumVer(graph g) {
	return g->n;	
}


// TODO: implement printGraph
//maybe change g->n/2 to g->n
void printGraph(graph g) {
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < (g->n/2); j++) {
			printf("%d ", g->matrix[i][j]);
		}
	}
	printf("\n");
}











