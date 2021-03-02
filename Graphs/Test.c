#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FunctionsGraph.h"

#define INF 9999

void dfs_connected_comps(ListGraph *lg, int node, int *color, struct LinkedList *component) {
    /* TODO */
    int parent[MAX_NODES], t_desc[MAX_NODES], t_fin[MAX_NODES];
    int time = 0;
    dfs_list_graph(lg, node, color, parent, t_desc, t_fin, &time, component);
}

void connected_components(ListGraph *lg, int *count) {
    /* TODO */
    struct LinkedList *component;
    int i, color[MAX_NODES];
    
    for(i=0;i<lg->nodes;i++)
        color[i] = 0;

    *count = 0;
    for(i=0;i<lg->nodes;i++)
        if(color[i] == 0)
        {
            component = malloc(sizeof(struct LinkedList));
            init_list(component);
            dfs_connected_comps(lg, i, color, component);
            (*count)++;
            print_int_linkedlist(component);
            free_list_improved(&component);
        }
}

void dfs_topo_sort(ListGraph *lg, int *color, int *t_fin) {
    /* TODO */
    int i, t_desc[MAX_NODES], parent[MAX_NODES], time;
    struct LinkedList *component;
    for(i=0;i<lg->nodes;i++)
    {
        color[i] = 0;
        t_fin[i] = 0;
    }

    time = 0;
    for(i=0;i<lg->nodes;i++)
        if(color[i] == 0)
        {
            component = malloc(sizeof(struct LinkedList));
            init_list(component);
            dfs_list_graph(lg, i, color, parent, t_desc, t_fin, &time, component);
            free_list_improved(&component);
        }
}

void topo_sort(int nodes, int *nodes_index, int *t_fin) {
    /* TODO */
    int aux, i, j;
    for(i=0;i<nodes;i++)
        for(j=i+1;j<nodes;j++)
            if(t_fin[i] < t_fin[j])
            {
                aux = t_fin[i];
                t_fin[i] = t_fin[j];
                t_fin[j] = aux;
                aux = nodes_index[i];
                nodes_index[i] = nodes_index[j];
                nodes_index[j] = aux;
            }
}

void init(ListGraph *lg, int *distance, int *parents)
{
    for (int i = 0; i < lg->nodes; i++)
    {
        distance[i] = INF;
        parents[i] = -1;
    }
}

void min_path(ListGraph *lg, int a, int b)
{
    int *visited = calloc(lg->nodes, sizeof(int));
    int *d = malloc(lg->nodes * sizeof(int));
    int *p = malloc(lg->nodes * sizeof(int));
    init(lg, d, p);

    struct Queue *q = malloc(sizeof(struct Queue));
    init_q(q);
    visited[a] = 1;
    d[a] = 0;
    int *c = malloc(100 * sizeof(int));
    enqueue_improved(q, &a, sizeof(int));
    while (!is_empty_q(q))
    {
        int v = *((int *)front(q));
        dequeue_improved(q);
        for (int i = 0; i < lg->nodes; i++)
        {
            if (has_edge_list_graph(lg, v, i) == 1 && visited[i] == 0)
            {
                {
                    visited[i] = 1;
                    p[i] = v;
                    d[i] = d[v] + 1;
                    c[i] = i;
                    enqueue_improved(q, &c[i], sizeof(int));
                }
            }
        }
    }
    if (d[b] != INF)
    {
        printf("Distanta minima intre %d si %d este: %d\n", a, b, d[b]);
        int cnt = 0;
        int route[10] = {0};
        int final = b;
        route[cnt++] = final;
        while (p[final] != -1) {
            route[cnt++] = p[final];
            final = p[final];
        }
        for (int i = d[b]; i >= 0; i--) {
            printf("%d ", route[i]);
        }
    }
    else
    {
        printf("Nu exista drum de la %d la %d.\n", a, b);
        return;
    }
    printf("\n\n");
    free(c);
    free(p);
    free(d);
    free(visited);
    purge_q_improved(q);
    free(q);
}

int check_bipartite(ListGraph *lg, int *nivel) {
    /* TODO */
    int i, node, node_top, neighbor_data;
    struct Queue *q;
    struct Node *neighbor;

    for(i=0;i<lg->nodes;i++)
        nivel[i] = -1;

    for(i=0;i<lg->nodes;i++)
    {
        node = i;
        if(nivel[node] == -1)
        {
            q = malloc(sizeof(struct Queue));
            init_q(q);
            nivel[node] = 0;
            enqueue_improved(q, &node, sizeof(int));

            while(!is_empty_q(q))
            {
                node_top = *(int*)front(q);
                dequeue_improved(q);
                neighbor = lg->neighbors[node_top]->head;
                while(neighbor != NULL)
                {
                    neighbor_data = *(int*)neighbor->data;
                    if(nivel[neighbor_data] == -1)
                    {
                        enqueue_improved(q, &neighbor_data, sizeof(int));
                        if(nivel[node_top] == 0)
                            nivel[neighbor_data] = 1;
                        else
                            nivel[neighbor_data] = 0;
                    }
                    else
                    {
                        if(nivel[node_top] == nivel[neighbor_data])
                        {
                            purge_q_improved(q);
                            free(q);
                            return 0;
                        }
                    }
                    neighbor = neighbor->next;
                }
            }
            purge_q_improved(q);
            free(q);
        }
    }
    return 1;
}

void create_graph(ListGraph *lg)
{
	int nodes, edges;
    int x[MAX_NODES], y[MAX_NODES];
	scanf("%d %d", &nodes, &edges);
    init_list_graph(lg, nodes);    

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }
}

int main() {
    
    ListGraph *lg;

    /* Ex 1 */
    lg = malloc(sizeof(ListGraph));
    create_graph(lg);
    
    int count = 0;
    printf("Componentele conexe\n");
    connected_components(lg, &count);
    printf("Sunt %d componente conexe\n\n", count);

    clear_list_graph(lg);
    free(lg);

    /* Ex 2 */ 
    int node1, node2;
    scanf("%d %d", &node1, &node2);

    lg = malloc(sizeof(ListGraph));
    create_graph(lg);

    min_path(lg, node1, node2);

    clear_list_graph(lg);
    free(lg);

    /* Ex 3 */
    int nodes_index[MAX_NODES], color[MAX_NODES], t_fin[MAX_NODES];

    lg = malloc(sizeof(ListGraph));
    create_graph(lg);

    for (int i = 0; i < lg->nodes; ++i)
        nodes_index[i] = i;

    printf("Sortare topologica\n");
    dfs_topo_sort(lg, color, t_fin);
    topo_sort(lg->nodes, nodes_index, t_fin);

    for(int i=0;i<lg->nodes;i++)
        printf("%d ", nodes_index[i]);
    printf("\n\n");

    clear_list_graph(lg);
    free(lg);
    
    /* Ex 4 */
    int nivel[MAX_NODES];
    
    lg = malloc(sizeof(ListGraph));
    create_graph(lg);

    if (check_bipartite(lg, nivel)) {
        printf("Graful este bipartit\n");
        for (int i = 0; i < lg->nodes; ++i) {
            if (nivel[i] == 1) {
                printf("%d ", i);
            }
        } 
        printf("\n");
        for (int i = 0; i < lg->nodes; ++i) {
            if (nivel[i] == 0) {
                printf("%d ", i);
            }
        } 
        printf("\n");
    } else {
        printf("Graful nu este bipartit\n");
    }

    clear_list_graph(lg);
    free(lg);
    
    return 0;
}
