#include <stdio.h>
#include <stdlib.h>

#include "Deque.h"

void init_deq(struct Deque *deq) {
    deq->list = malloc(sizeof(struct LinkedList));
    if (deq->list == NULL) {
        perror("Not enough memory to initialize the queue!");
        return;
    }

    init_list(deq->list);
}

int get_size_deq(struct Deque *deq) {
    /* TODO */
    return deq->list->size;
}

int is_empty_deq(struct Deque *deq) {
    /* TODO */
    if(deq->list->size == 0)
    	return 1;
    return 0;
}

void* front(struct Deque *deq) {
    /* TODO */
    if(deq->list->head == NULL)
    	return NULL;
    return deq->list->head->data;
}

void* back(struct Deque *deq) {
    if(deq->list->head == NULL)
        return NULL;
    return deq->list->tail->data;
}

void front_dedeq(struct Deque *deq) {
    /* TODO */
    struct Node *first;
    first = remove_nth_node(deq->list, 0);
    free(first->data);
    free(first);
}

void back_dedeq(struct Deque *deq) {
    struct Node *last;
    last = remove_nth_node(deq->list, deq->list->size);
    free(last->data);
    free(last);
}

void front_endeq(struct Deque *deq, void *new_data, int new_data_bytes) {
    /* TODO */
    add_nth_node_improved(deq->list, 0, new_data, new_data_bytes);
}

void back_endeq(struct Deque *deq, void *new_data, int new_data_bytes) {
    add_nth_node_improved(deq->list, deq->list->size, new_data, new_data_bytes);
}

void clear_deq(struct Deque *deq) {
    /* TODO */
    while(deq->list->size > 0)
		front_dedeq(deq);
}

void purge_deq(struct Deque *deq) {
    /* TODO */
    free_list_improved(&deq->list);
}
