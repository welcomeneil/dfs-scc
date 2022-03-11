#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

// structs --------------------------------------------------------------------

// Private GraphObj type.
typedef struct GraphObj {
    List *list_array;
    int *color_array;
    int *parent_array;
    int *disc_array;
    int *finish_array;
    int order;
    int size;
} GraphObj;

// Private Helper Function -----------------------------------------------------------

// Helper function declaration.
void visit(Graph G, List S, int u, int *time);

// Helper function for DFS().
void visit(Graph G, List S, int u, int *time) {
    int adjacent_vert;
    *time += 1;
    G->disc_array[u] = *time;
    G->color_array[u] = GRAY;
    moveFront(G->list_array[u]);
    for (int i = 0; i < length(G->list_array[u]); i += 1) {
        adjacent_vert = get(G->list_array[u]);
        if (G->color_array[adjacent_vert] == WHITE) {
            G->parent_array[adjacent_vert] = u;
            visit(G, S, adjacent_vert, time);
        }
        moveNext(G->list_array[u]);
    }
    G->color_array[u] = BLACK;
    *time += 1;
    G->finish_array[u] = *time;
    prepend(S, u);
    return;
}

// Constructors-Destructors ---------------------------------------------------

// Graph constructor.
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->list_array = (List *) malloc((n + 1)*sizeof(List));
    for (int i = 1; i < n + 1; i += 1) {
        G->list_array[i] = newList();
    }

    G->color_array = (int *) calloc(n + 1, sizeof(int));
    G->parent_array = (int *) calloc(n + 1, sizeof(int));
    for (int i = 1; i < n + 1; i += 1) {
        G->parent_array[i] = NIL;
    }

    G->disc_array = (int *) calloc(n + 1, sizeof(int));
    for (int i = 1; i < n + 1; i += 1) {
        G->disc_array[i] = UNDEF;
    }

    G->finish_array = (int *) calloc(n + 1, sizeof(int));
    for (int i = 1; i < n + 1; i += 1) {
        G->finish_array[i] = UNDEF;
    }

    G->order = n;
    G->size = 0;
    return G;
}

// Graph Destructor.
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL && (*pG)->list_array && (*pG)->color_array && (*pG)->parent_array && (*pG)->disc_array && (*pG)->finish_array) { 
        for (int i = 1; i < getOrder(*pG) + 1; i += 1) {
            freeList(&(*pG)->list_array[i]);
        }
        free((*pG)->list_array);
        free((*pG)->color_array);
        free((*pG)->parent_array);
        free((*pG)->disc_array);
        free((*pG)->finish_array);
        free(*pG);
        *pG = NULL;
    }
    return;
}

// Accessor functions -----------------------------------------------------------

// Returns the order of the Graph.
int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// Returns the size of the Graph.
int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

// Returns the parent of vertex u in the DFS forest created by DFS()
// Returns NIL if a DFS hasn't ocurred yet (a parent may be NIL even if DFS has occured).
// Pre: 1 <= u <= getOrder(G) (the order of the graph/number of vertices).
int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getParent() with invalid vertex/vertices\n");
        exit(EXIT_FAILURE);
    }
    return G->parent_array[u];
}

// Returns the discover time of a vertex after DFS().
// If DFS() hasn't been called, returns UNDEF.
// Pre: 1 <= u <= getOrder(G) (the order of the graph/number of vertices).
int getDiscover(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getDiscover() with invalid vertex/vertices\n");
        exit(EXIT_FAILURE);
    }
    return G->disc_array[u];
}

// Returns the finish time of a vertex after DFS().
// If DFS() hasn't been called, returns UNDEF.
// Pre: 1 <= u <= getOrder(G) (the order of the graph/number of vertices).
int getFinish(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getFinish() with invalid vertex/vertices\n");
        exit(EXIT_FAILURE);
    }
    return G->finish_array[u];
}

// Manipulation procedures ----------------------------------------------------

// Adds an undirected edge between vertex u and v.
// The vertex labels for each edge are maintained in sorted order.
// Pre: 1 <= u <= getOrder(G)
// Pre: 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addEdge() with invalid vertex/vertices\n");
        exit(EXIT_FAILURE);
    }

    if (length(G->list_array[u]) == 0) {
        append(G->list_array[u], v);
    } else {
        int j;
        moveFront(G->list_array[u]);
            while (index(G->list_array[u]) != -1) {
                j = get(G->list_array[u]);
                if (v < j) {
                    insertBefore(G->list_array[u], v);
                    break;
                }
                moveNext(G->list_array[u]);
            }
            if (index(G->list_array[u]) == -1) {
                append(G->list_array[u], v);
            }
    }
    
    if (length(G->list_array[v]) == 0) {
        append(G->list_array[v], u);
    } else {
        int j;
        moveFront(G->list_array[v]);
            while (index(G->list_array[v]) != -1) {
                j = get(G->list_array[v]);
                if (u < j) {
                    insertBefore(G->list_array[v], u);
                    break;
                }
                moveNext(G->list_array[v]);
            }
            if (index(G->list_array[v]) == -1) {
                append(G->list_array[v], u);
            }
    }
    G->size += 1;
    return;
}

// Adds a directed edge from u to v.
// The vertex labels for each edge are maintained in sorted order.
// Pre: 1 <= u <= getOrder(G)
// Pre: 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addArc() with invalid vertex/vertices\n");
        exit(EXIT_FAILURE);
    }

    if (length(G->list_array[u]) == 0) {
        append(G->list_array[u], v);
    } else {
        int j;
        moveFront(G->list_array[u]);
            while (index(G->list_array[u]) != -1) {
                j = get(G->list_array[u]);
                if (v < j) {
                    insertBefore(G->list_array[u], v);
                    break;
                }
                moveNext(G->list_array[u]);
            }
            if (index(G->list_array[u]) == -1) {
                append(G->list_array[u], v);
            }
    }
    G->size += 1;
    return;
}

// Performs DFS on the given graph G, pushing vertices onto the "stack" S.
// Pre: length(S) == getOrder(G) (the order of the graph/number of vertices).
void DFS(Graph G, List S) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "Graph Error: calling DFS() with invalid stack\n");
        exit(EXIT_FAILURE);
    }

    int time = 0;
    int stack_vertex;
    List S_copy = copyList(S);
    clear(S);

    // Initializing vertices to undiscovered and parents to NIL.
    for (int i = 1; i < getOrder(G) + 1; i += 1) {
        G->color_array[i] = WHITE;
    }
    for (int i = 1; i < getOrder(G) + 1; i += 1) {
        G->parent_array[i] = NIL;
    }

    moveFront(S_copy);
    for (int i = 0; i < length(S_copy); i += 1) {
        stack_vertex = get(S_copy);
        if (G->color_array[stack_vertex] == WHITE) {
            visit(G, S, stack_vertex, &time);
        }
        moveNext(S_copy);
    }

    freeList(&S_copy);
    return;
}

// Other operations ------------------------------------------------------------

// Returns a new transpose graph of a graph G.
Graph transpose(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling transpose() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    int adjacent_vert;
    Graph transpose = newGraph(getOrder(G));

    for (int i = 1; i < getOrder(G) + 1; i += 1) {
        moveFront(G->list_array[i]);
        for (int j = 0; j < length(G->list_array[i]); j += 1) {
            adjacent_vert = get(G->list_array[i]);
            append(transpose->list_array[adjacent_vert], i);
            moveNext(G->list_array[i]);
        }
    }
    return transpose;
}

// Returns a new copy of graph G.
Graph copyGraph(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    int adjacent_vert;
    Graph copy = newGraph(getOrder(G));

    for (int i = 1; i < getOrder(G) + 1; i += 1) {
    moveFront(G->list_array[i]);
        for (int j = 0; j < length(G->list_array[i]); j += 1) {
            adjacent_vert = get(G->list_array[i]);
            append(copy->list_array[i], adjacent_vert);
            moveNext(G->list_array[i]);
        }
    }
    return copy;
}

// Prints the Graph G to out.
void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 1; i < getOrder(G) + 1; i += 1) {
        fprintf(out, "%d: ", i);
        printList(out, G->list_array[i]);
        fprintf(out, "\n");
    }
    return;
}