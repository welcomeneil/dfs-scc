#include "List.h"

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#define UNDEF -1
#define NIL 0
#define WHITE -10
#define GRAY -20
#define BLACK -30

// Exported type --------------------------------------------------------------

typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

Graph newGraph(int n);

void freeGraph(Graph* pG);

// Accessor functions -----------------------------------------------------------

int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

// Manipulation procedures ----------------------------------------------------

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List S);

// Other operations ------------------------------------------------------------

Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

#endif