#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

void init_stack(struct Stack *stack) {
    stack->list = malloc(sizeof(struct LinkedList));
    if (stack->list == NULL) {
        perror("Not enough memory to initialize the stack!");
        return;
    }

    init_list(stack->list);
}

int get_size_stack(struct Stack *stack) {
    /* TODO */
    return stack->list->size;
}

int is_empty_stack(struct Stack *stack) {
    /* TODO */
    if(stack->list->size == 0)
    	return 1;
    return 0;
}

void* peek_stack(struct Stack *stack) {
    /* TODO */
    if(stack->list->head == NULL)
    	return NULL;
    return stack->list->tail->data;
}

void pop_stack(struct Stack *stack) {
    /* TODO */
    struct Node *last;
    last = remove_nth_node(stack->list, stack->list->size);
    free(last);
}

void pop_stack_improved(struct Stack *stack) {
    struct Node *last;
    last = remove_nth_node(stack->list, stack->list->size);
    free(last->data);
    free(last);
}


void push_stack(struct Stack *stack, void *new_data) {
    /* TODO */
    add_nth_node(stack->list, stack->list->size, new_data);
}

void push_stack_improved(struct Stack *stack, void *new_data, int new_data_bytes) {
    add_nth_node_improved(stack->list, stack->list->size, new_data, new_data_bytes);
}

void clear_stack(struct Stack *stack) {
    /* TODO */
	while(stack->list->size > 0)
		pop_stack(stack);
}

void purge_stack(struct Stack *stack) {
    /* TODO */
    free_list(&stack->list);
}

void purge_stack_improved(struct Stack *stack) {
    free_list_improved(&stack->list);
}
