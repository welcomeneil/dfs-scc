# Depth-First Search - Finding Strongly Connected Components

Finds the strongly connected components of a given graph. The input file should be in the following format:
```
8
1 2
2 3
2 5
2 6
3 4
3 7
4 3
4 8
5 1
5 6
6 7
7 6
7 8
8 8
0 0
```
The first line specifies the number of vertices the graph contains. Each subsequent line until the "0 0" terminating dummy line specifies the edges between vertices.

## Files

List.h: Contains the interface for our List ADT

List.c: Contains the implementation for our List ADT

Graph.h: Contains the interface for our Graph ADT

Graph.c: Contains the implementation for our Graph ADT

GraphTest.c: Contains testing used for our Graph ADT

FindComponents.c: 

-Where our main() is located; finds and prints the strongly connected components of a graph G.

## Building

Build the program with:

```
$ make
```
or
```
$ make FindComponents
```

## Running

Run the program with:

```
$ ./FindComponents <input file> <output file>
```
