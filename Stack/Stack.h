#ifndef __STACK_H__
#define __STACK_H__

#include "LinkedList.h"

struct Stack {
    struct LinkedList *list;
};

void init_stack(struct Stack *stack);

int get_size_stack(struct Stack *stack);

int is_empty_stack(struct Stack *stack);

void* peek_stack(struct Stack *stack);

void pop_stack(struct Stack *stack);

void pop_stack_improved(struct Stack *stack);

void push_stack(struct Stack *stack, void *new_data);

void push_stack_improved(struct Stack *stack, void *new_data, int new_data_bytes);

void clear_stack(struct Stack *stack);

void purge_stack(struct Stack *stack);

void purge_stack_improved(struct Stack *stack);

#endif /* __STACK_H__ */
