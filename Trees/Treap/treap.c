#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include "treap.h"
#define MAX_PRIORITY 1000

// Creeaza structura Treap-ului
Treap_tree* treap_create(int (*cmp)(void*, void*)) {
	srand(time(NULL));
	Treap_tree *tree = malloc(sizeof(Treap_tree));
	if (tree == NULL) {
		return NULL;
	}
	tree->compar = cmp;
	tree->root = NULL;
	return tree;
}

void node_free(Node **node) {

	if (!(*node)) {
		return;
	}
	node_free(&(*node)->left);
	node_free(&(*node)->right);

	free((*node)->data);
	free(*node);
}

void treap_free(Treap_tree *tree) {
	if (tree->root != NULL) {
		node_free(&tree->root);
	}
	free(tree);
}

/* Creeaza un nod 
 * @param1: Valoarea ce trebuie pusa in nod.
 * @param2: Numarul de octeti pe care scrie valoarea.
 */
Node* node_create(void *value, int data_size) {
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		return NULL;
	}
	node->data = malloc(data_size);

	// Copiere octet cu octet din value, in nodul curent.
    for (int i = 0; i < data_size; ++i) {
        *(char *)(node->data + i) = *(char *)(value + i);
    }

    // Nodurile frunze au inaltimea 0.
	node->priority = rand() % MAX_PRIORITY;
	node->left = NULL;
	node->right = NULL;

	return node;
}

// Nodurile NULL au prioritatea -1 pentru a pastra proprietatea de max-heap.
int priority(Node *node) {
	if (node == NULL) {
		return -1;
	}
	return node->priority;
}

/* Rotire dreapta
 * Pentru a nu fi nevoie sa mentinem pointer catre nodul parinte,
 * se vor folosi pointeri la noduri
 *
 *      node  			    lson
 *     /    \			   /    \ 
 *   lson    y    --->    x    node
 *   /  \     		           /   \ 
 *  x   lrson                lrson  y
 */
void rotate_right(Node **node) {
	// TODO: Completati rotire dreapta
	if(!(*node) || !(*node)->left)
		return;

	Node *left = (*node)->left;
	(*node)->left = left->right;
	left->right = *node;
	*node = left;
}

/* Rotire stanga
 * Pentru a nu fi nevoie sa mentinem pointer catre nodul parinte,
 * se vor folosi pointeri la noduri
 *
 *     node  			    rson
 *    /    \			   /    \ 
 *   x     rson    --->  node    y
 *         /   \		 /   \
 *       rlson  y       x   rlson
 */	
void rotate_left(Node **node) {
	// TODO: Completati rotire stanga.
	if(!(*node) || !(*node)->right)
		return;

	Node *right = (*node)->right;
	(*node)->right = right->left;
	right->left = *node;
	*node = right;
}

/* Inserare in Treap
 * 
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in Treap.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din Treap.
 */
void treap_insert(Node **node, void *value, int data_size, int (*compar)(void*, void*)) {
	// TODO: Inserati recursiv in arbore
	// TODO: Reechilibrare arbore
	if(!(*node))
	{
		*node = node_create(value, data_size);
		return;
	}
	if(compar(value, (*node)->data) < 0)
	{
		treap_insert(&(*node)->left, value, data_size, compar);
		if(priority(*node) < priority((*node)->left))
			rotate_right(node);
	}
	else
	{
		treap_insert(&(*node)->right, value, data_size, compar);
		if(priority(*node) < priority((*node)->right))
			rotate_left(node);
	}
}

/* Stergere din Treap
 *
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in Treap.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din Treap.
 */
void treap_delete(Node **node, void *value, int data_size, int (*compar)(void*, void*)) {
	// TODO: Stergeti recursiv din arbore
	if(!(*node))
		return;
	if(compar(value, (*node)->data) < 0)
		treap_delete(&(*node)->left, value, data_size, compar);
	else if(compar(value, (*node)->data) > 0)
		treap_delete(&(*node)->right, value, data_size, compar);
	else
	{
		if(!(*node)->left && !(*node)->right)
		{
			free((*node)->data);
			free(*node);
			*node = NULL;
		}
		else
		{
			if(priority((*node)->left) > priority((*node)->right))
				rotate_right(node);
			else
				rotate_left(node);
			treap_delete(node, value, data_size, compar);
		}
	}
}

void* get_key(Node *node, void *value, int data_size, int (*compar)(void*, void*)) {
	// TODO: Cautarea unei valori in arbore
	if(!node)
		return NULL;
	if(compar(value, node->data) == 0)
		return node->data;
	if(compar(value, node->data) < 0)
		return get_key(node->left, value, data_size, compar);
	else
		return get_key(node->right, value, data_size, compar);
}

/* Verifica daca un arbore respecta proprietatile unui treap
 *
 * @param1: Nodul curent in parcurgerea recursiva.
 * @param2: Functia de comparare a datelor din fiecare nod.
 * @return: Daca arborele e Treap, vom returna numarul de noduri al arborelui,
 * 			altfel, vom returna o valoare negativa. 
 */
int check_treap(Node *node, int (*compar)(void*, void*)) {
	if (node == NULL) {
		return 0;
	} else if (node->left == NULL && node->right == NULL) {
		return 1;
	} else if (node->left == NULL) {
		if (priority(node) >= priority(node->right) 
			&& compar(node->data, node->right->data) <= 0) {
			return 1 + check_treap(node->right, compar);
		}
		return INT_MIN;
	} else if (node->right == NULL) {
		if (priority(node) >= priority(node->left) 
			&& compar(node->data, node->left->data) >= 0) {
			return 1 + check_treap(node->left, compar);
		}
		printf("%d %d %d\n", priority(node), priority(node->left), priority(node->right));
		return INT_MIN;
	} else {
		if (priority(node) >= priority(node->left) && priority(node) >= priority(node->right)
			&& compar(node->data, node->left->data) >= 0 
			&& compar(node->data, node->right->data) <= 0) {
			return 1 + check_treap(node->left, compar) + check_treap(node->right, compar);
		}
		printf("%d %d %d\n", priority(node), priority(node->left), priority(node->right));
		return INT_MIN;
	}
}
