#ifndef __FUNCTIONSGRAPH_H__
#define __FUNCTIONSGRAPH_H__

#include "Stack.h"
#include "Queue.h"
#include "ListGraph.h"

#define MAX_NODES 100

void print_list_graph(ListGraph *lg);

void dfs_list_graph(ListGraph *lg, int node, int *color, int *parent, int *t_desc, int *t_fin, int *time, struct LinkedList *component);

void bfs_list_graph(ListGraph *lg, int node, int *color, int *parent, int *dist);

#endif /* __FUNCTIONSGRAPH_H__ */