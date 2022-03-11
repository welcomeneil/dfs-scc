#include "Graph.h"
#include <stdlib.h>

int main(int argc, char * argv[]) {
    
    FILE *in_file, *out_file;

    int vertices;
    int end_1;
    int end_2;
    int scc_counter = 0;
    int vertex;

    // Checks command line for correct number of arguments.
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the infile for reading.
    // If the file cannot be opened, produce an error statement and end the program.
    in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open the outfile for writing.
    // If the file cannot be opened, produce an error statement and end the program.
    out_file = fopen(argv[2], "w");
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Scans in the number of vertices and creates a graph G.
    fscanf(in_file, "%d\n", &vertices);
    Graph G = newGraph(vertices);

    // Creates the initial stack of vertices from 1,2,...,n
    List S = newList();
    for (int i = 1; i < vertices + 1; i += 1) {
        append(S, i);
    }

    // Scans in all edges and adds them to the graph G.
    do {
        fscanf(in_file, "%d" "%d\n", &end_1, &end_2);
        if (end_1 == 0 && end_2 == 0) {
            break;
        }
        addArc(G, end_1, end_2);
    } while (true);

    fprintf(out_file, "Adjacency list representation of G:\n");
    printGraph(out_file, G);
    fprintf(out_file, "\n");

    // Runs DFS on G and the transpose of G.
    DFS(G, S);
    Graph trans = transpose(G);
    DFS(trans, S);

    // Finds the number of SCC's.
    moveFront(S);
    for (int i = 0; i < length(S); i += 1) {
        vertex = get(S);
        if (getParent(trans, vertex) == NIL) {
            scc_counter += 1;
        }
        moveNext(S);
    }

    fprintf(out_file, "G contains %d strongly connected components:\n", scc_counter);

    // Prints out the SCC's in topological sorted order to the outfile.
    List scc = newList();
    scc_counter = 0;
    moveBack(S);
    for (int i = 0; i < length(S); i += 1) {
        vertex = get(S);
        prepend(scc, vertex);
        if (getParent(trans, vertex) == NIL) {
            scc_counter += 1;
            fprintf(out_file, "Component %d: ", scc_counter);
            printList(out_file, scc);
            fprintf(out_file, "\n");
            clear(scc);
        }
        movePrev(S);
    }

    // Freeing of allocated memory.
    freeGraph(&G);
    freeGraph(&trans);
    freeList(&S);
    freeList(&scc);
    
    // Closing of files.
    fclose(in_file);
    fclose(out_file);

    return 0;
}
