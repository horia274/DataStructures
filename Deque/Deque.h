#ifndef __DEQUE_H__
#define __DEQUE_H__

#include "LinkedList.h"

struct Deque {
    struct LinkedList *list;
};

void init_deq(struct Deque *deq);

int get_size_deq(struct Deque *deq);

int is_empty_deq(struct Deque *deq);

void* front(struct Deque *deq);

void* back(struct Deque *deq);

void front_dedeq(struct Deque *deq);

void back_dedeq(struct Deque *deq);

void front_endeq(struct Deque *deq, void *new_data, int new_data_bytes);

void back_endeq(struct Deque *deq, void *new_data, int new_data_bytes);

void clear_deq(struct Deque *deq);

void purge_deq(struct Deque *deq);

#endif /* __QUEUE_H__ */
