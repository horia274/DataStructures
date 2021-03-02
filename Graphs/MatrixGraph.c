#include <stdlib.h>
#include <stdio.h>

#include "MatrixGraph.h"
#include "Stack.h"
#include "Queue.h"

/**
 * Initializeaza graful cu numarul de noduri primit ca parametru si aloca
 * memorie pentru matricea de adiacenta a grafului.
*/
void init_matrix_graph(MatrixGraph *graph, int nodes) {
    /* TODO */
    int i,j;
    graph->nodes = nodes;
    graph->matrix = malloc(nodes * sizeof(int*));
    for(i=0;i<nodes;i++)
    	graph->matrix[i] = malloc(nodes * sizeof(int));
    for(i=0;i<nodes;i++)
    	for(j=0;j<nodes;j++)
    		graph->matrix[i][j] = 0;
}

/* Adauga o muchie intre nodurile sursa si destinatie */
void add_edge_matrix_graph(MatrixGraph *graph, int src, int dest) {
    /* TODO */
    graph->matrix[src][dest] = 1;
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int has_edge_matrix_graph(MatrixGraph *graph, int src, int dest) {
    /* TODO */
    return graph->matrix[src][dest];
}

/* Elimina muchia dintre nodurile sursa si destinatie */
void remove_edge_matrix_graph(MatrixGraph *graph, int src, int dest) {
    /* TODO */
    graph->matrix[src][dest] = 0;
}

/* Elibereaza memoria folosita de matricea de adiacenta a grafului */
void clear_matrix_graph(MatrixGraph *graph) {
    /* TODO */
    int i;
    for(i=0;i<graph->nodes;i++)
    	free(graph->matrix[i]);
    free(graph->matrix);
}
