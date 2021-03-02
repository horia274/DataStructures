#include <stdio.h>
#include <stdlib.h>

#include "FunctionsGraph.h"

void print_list_graph(ListGraph *lg) {
    /* TODO */
    int i;
    for(i=0;i<lg->nodes;i++)
    {
        printf("%d: ", i);
        print_int_linkedlist(lg->neighbors[i]);
    }
    printf("\n");
}

void dfs_list_graph(ListGraph *lg, int node, int *color, int *parent, int *t_desc, int *t_fin, int *time, struct LinkedList *component) {
    /* TODO */
    int i, node_top;
    struct Node *neighbor;
    struct Stack *stack;

    for(i=0;i<lg->nodes;i++) {
        parent[i] = -1;
        t_desc[i] = 0;
    }

    stack = malloc(sizeof(struct Stack));
    init_stack(stack);

    t_desc[node] = *time;
    color[node] = 1;
    add_nth_node_improved(component, component->size, &node, sizeof(int));
    push_stack_improved(stack, &node, sizeof(int));

    while(!is_empty_stack(stack)) {
        node_top = *(int*)peek_stack(stack);
        neighbor = lg->neighbors[node_top]->head;
        while(neighbor != NULL && color[*(int*)neighbor->data] != 0)
            neighbor = neighbor->next;
        if(neighbor != NULL)
        {
            parent[*(int*)neighbor->data] = node_top;
            (*time)++;
            t_desc[*(int*)neighbor->data] = *time;
            color[*(int*)neighbor->data] = 1;
            add_nth_node_improved(component, component->size, (int*)neighbor->data, sizeof(int));
            push_stack_improved(stack, (int*)neighbor->data, sizeof(int));
        }
        else
        {
            (*time)++;
            t_fin[node_top] = (*time);
            color[node_top] = 2;
            pop_stack_improved(stack);
        }
    }
    purge_stack_improved(stack);
    free(stack);
}

void bfs_list_graph(ListGraph *lg, int node, int *color, int *parent, int *dist) {
    /* TODO */
    int i, node_top, neighbor_data;
    struct Queue *q;
    struct Node *neighbor;
    for(i=0;i<lg->nodes;i++)
    {
        color[i] = 0;
        parent[i] = -1;
        dist[i] = -1;
    }

    color[node] = 1;
    dist[node] = 0;

    q = malloc(sizeof(struct Queue));
    init_q(q);
    // printf("%d ", node);
    enqueue_improved(q, &node, sizeof(int));

    while(!is_empty_q(q))
    {
        node_top = *(int*)front(q);
        dequeue_improved(q);
        neighbor = lg->neighbors[node_top]->head;
        while(neighbor != NULL)
        {
            neighbor_data = *(int*)neighbor->data;
            if(color[neighbor_data] == 0)
            {
                color[neighbor_data] = 1;
                parent[neighbor_data] = node_top;
                dist[neighbor_data] = dist[node_top] + 1;
                // printf("%d ", neighbor_data);
                enqueue_improved(q, &neighbor_data, sizeof(int));
            }
            neighbor = neighbor->next;
        }
        color[node_top] = 2;
    }

    // printf("\n");
    purge_q_improved(q);
    free(q);
}
