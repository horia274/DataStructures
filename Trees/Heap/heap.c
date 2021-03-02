/**
 * SD, 2020
 * 
 * Lab #9, BST & Heap
 * 
 * Task #2 - Heap implementation
 */

#include "Heap.h"

void init_heap(struct Heap *heap, int capacity, int (*cmp_f)(void*, void*))
{
	heap->cmp       = cmp_f;
	heap->size      = 0;
	heap->capacity  = capacity;
	heap->arr       = malloc(heap->capacity * sizeof(void*));
}

void __heap_insert_fix(struct Heap *heap, int pos)
{
	void *tmp;
	int p = GO_UP(pos);

	/* TODO */
	while(p >= 0 && heap->cmp(heap->arr[p], heap->arr[pos]) > 0) {
		tmp = heap->arr[p];
		heap->arr[p] = heap->arr[pos];
		heap->arr[pos] = tmp;

		pos = p;
		p = GO_UP(pos);
	}
}

void heap_insert(struct Heap *heap, void *new_data, int new_data_bytes)
{
	heap->arr[heap->size] = malloc(new_data_bytes);
	memcpy(heap->arr[heap->size], new_data, new_data_bytes);

	__heap_insert_fix(heap, heap->size);

	heap->size++;
}

void* heap_top(struct Heap *heap)
{
	/* TODO */
	return heap->arr[0];
}

void __heap_pop_fix(struct Heap *heap, int pos)
{
	void *tmp;
	int p = pos;
	int l = GO_LEFT(pos);
	int r = GO_RIGHT(pos);

	/* TODO */
	while(1) {
		if(r >= heap->size) {
			if(l >= heap->size)
				break;
			else if(heap->cmp(heap->arr[l], heap->arr[p]) < 0) {
				tmp = heap->arr[l];
				heap->arr[l] = heap->arr[p];
				heap->arr[p] = tmp;
				p = l;
				l = GO_LEFT(p);
				r = GO_RIGHT(p);
			}
			else
				break;
		}
		else {
			if(heap->cmp(heap->arr[l], heap->arr[r]) < 0 &&
				heap->cmp(heap->arr[l], heap->arr[p]) < 0) {
				tmp = heap->arr[l];
				heap->arr[l] = heap->arr[p];
				heap->arr[p] = tmp;
				p = l;
				l = GO_LEFT(p);
				r = GO_RIGHT(p);
			}
			else if(heap->cmp(heap->arr[l], heap->arr[r]) > 0 && 
					heap->cmp(heap->arr[r], heap->arr[p]) < 0) {
				tmp = heap->arr[r];
				heap->arr[r] = heap->arr[p];
				heap->arr[p] = tmp;
				p = r;
				l = GO_LEFT(p);
				r = GO_RIGHT(p);
			}
			else
				break;
		}
	}
}

void heap_pop(struct Heap *heap, void (free_function)(void*))
{
	free_function(heap->arr[0]);

	heap->arr[0] = heap->arr[heap->size - 1];

	heap->size--;

	__heap_pop_fix(heap, 0);
}

int is_empty_heap(struct Heap *heap)
{
	return heap->size <= 0;
}

void free_heap(struct Heap *heap, void (free_function)(void*))
{
	/* TODO */
	for(int i = 0; i < heap->size; i++)
		free_function(heap->arr[i]);
	free(heap->arr);
	free(heap);
}
