#include <stdlib.h>
#include <stdio.h>

#include "ListGraph.h"

void init_list_graph(ListGraph *graph, int nodes) {
    /* TODO */
    int i;
    graph->nodes = nodes;
    graph->neighbors = malloc(nodes * sizeof(struct LinkedList*));
    for(i=0;i<nodes;i++)
    {
    	graph->neighbors[i] = malloc(sizeof(struct LinkedList));
    	init_list(graph->neighbors[i]);
    }
}

void add_edge_list_graph(ListGraph *graph, int src, int *dest) {
    /* TODO */
    add_nth_node_improved(graph->neighbors[src], graph->neighbors[src]->size, dest, sizeof(int));
}

int has_edge_list_graph(ListGraph *graph, int src, int dest) {
    /* TODO */
    struct Node *curr;
    curr = graph->neighbors[src]->head;
    while(curr != NULL)
    {
    	if(*(int*)curr->data == dest)
    		return 1;
    	curr = curr->next;
    }
    return 0;
}

struct LinkedList* get_neighbours_list_graph(ListGraph *graph, int node) {
    /* TODO */
    return graph->neighbors[node];
}

void remove_edge_list_graph(ListGraph *graph, int src, int dest) {
    /* TODO */
    struct Node *curr;
    int poz;
    curr = graph->neighbors[src]->head;
    poz = 0;
    while(curr != NULL)
    {
    	if(*(int*)curr->data == dest)
    	{
    		curr = remove_nth_node(graph->neighbors[src], poz);
    		free(curr->data);
    		free(curr);
    		return;
    	}
    	else
    	{
    		poz++;
   			curr = curr->next;
    	}
    }
}

void clear_list_graph(ListGraph *graph) {
    /* TODO */
    int i;
    for(i=0;i<graph->nodes;i++)
    	free_list_improved(&graph->neighbors[i]);
    free(graph->neighbors);
}
