// struct defs
// using matrix representation for graph
typedef struct graphObj{int n; int** matrix;} graphObj;
typedef graphObj* graph;


// Graph constructor
graph createGraph(int num);

// graph destructor
void destructGraph(graph g);

// adds an edge from vertex i to vertex j
void addEdge(graph g, int i, int j);

// removes edge from vertex i to vertex j
void removeEdge(graph g, int i, int j);

// indicates if graph g has edge from vertex i to vertex j
int hasEdge(graph g, int i, int j);

// takes in an empty list and adds to it all outgoing edges out of vertex i
void outEdges(graph g, int i, node** list);

// takes in an empty list and adds to it all incoming edges into vertex j
void inEdges(graph g, int j, node** list);

// prints the matrix representation of the graph
void printGraph(graph g);

// getter function for number of vertices in a graph
int getNumVer(graph g);

