#include <stdio.h>
#include <stdlib.h>

#include "CircularDoublyLinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct CircularDoublyLinkedList *list) {
    /* TODO */
    list->head = NULL;
    list->size = 0;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Daca n >= nr_noduri, atunci se intoarce nodul de pe pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe
 * lista si am trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem afla pozitia dorita fara sa
 * simulam intreaga parcurgere?
 * Daca n < 0, eroare.
 */
struct Node* get_nth_node(struct CircularDoublyLinkedList *list, int n) {
    /* TODO */
	struct Node *curr;
	int i;
	if(n < 0 || list == NULL || list->head == NULL)
		return NULL;
	curr = list->head;
    for(i=0;i<(n%list->size);i++)
    	curr = curr->next;
    return curr;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0).
 * Cand indexam pozitiile nu "ciclam" pe lista circulara ca la get, ci consideram nodurile in ordinea de la head la
 * ultimul (adica acel nod care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci adaugam nodul
 * nou la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct CircularDoublyLinkedList *list, int n, void *new_data) {
    /* TODO */
    struct Node *new,*curr;
    int i;
    if(n < 0 || list == NULL)
    	return;
    new = malloc(sizeof(struct Node));
    new->data = new_data;
	if(list->head == NULL)
    {
    	list->head = new;
    	new->next = new;
    	new->prev = new;
    }
    else
    {
	    if(n >= list->size)
	    {
	    	new->next = list->head;
	    	new->prev = list->head->prev;
	    	list->head->prev->next = new;
	    	list->head->prev = new;
	    }
	    if(n == 0)
	   	{
	   		new->next = list->head;
	   		new->prev = list->head->prev;
	   		list->head->prev->next = new;
	   		list->head->prev = new;
	   		list->head = new;	
	   	}
	    if(n > 0 && n < list->size)
	   	{
	   		curr = list->head;
	   		for(i=0;i<n;i++)
	   			curr = curr->next;
	   		curr->prev->next = new;
	   		new->prev = curr->prev;
	   		new->next = curr;
	   		curr->prev = new;
	   	}
	}
	list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct CircularDoublyLinkedList *list, int n) {
    /* TODO */
	struct Node *curr;
	int i;
	if(list == NULL || n < 0)
		return NULL;
	if(list->size == 1)
	{
		curr = list->head;
		list->head = NULL;
	}
	else
	{
		if(n >= list->size-1)
		{
			curr = list->head->prev;
			curr->prev->next = list->head;
			list->head->prev = curr->prev;
		}
		else
		{
			curr = list->head;
			for(i=0;i<n;i++)
				curr = curr->next;
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			if(n == 0)
				list->head = curr->next;
		}
	}
	list->size--;
	return curr;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct CircularDoublyLinkedList *list) {
    /* TODO */
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista.
 */
void free_list(struct CircularDoublyLinkedList **pp_list) {
    /* TODO */
	struct Node *curr,*prev;
	int i;
	if(*pp_list == NULL)
		return;
	curr = (*pp_list)->head;
	for(i=0;i<(*pp_list)->size;i++)
	{
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_int_list(struct CircularDoublyLinkedList *list) {
    /* TODO */
	struct Node *curr;
	int i;
	if(list == NULL)
		return;
	curr = list->head;
	for(i=0;i<list->size;i++)
	{
		printf("%d ",*(int*)(curr->data));
		curr = curr->next;
	}
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_string_list(struct CircularDoublyLinkedList *list) {
    /* TODO */
	struct Node *curr;
	int i;
	if(list == NULL)
		return;
	curr = list->head;
	for(i=0;i<list->size;i++)
	{
		printf("%s ",(char*)(curr->data));
		curr = curr->next;
	}
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la stanga in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_left_circular(struct CircularDoublyLinkedList *list, struct Node *start) {
    /* TODO */
	struct Node *curr;
	int i;
	if(list == NULL)
		return;
	curr = start;
	for(i=0;i<list->size;i++)
	{
		printf("%d ",*(int*)(curr->data));
		curr = curr->prev;
	}
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_right_circular(struct CircularDoublyLinkedList *list, struct Node *start) {
    /* TODO */
	struct Node *curr;
	int i;
	if(list == NULL)
		return;
	curr = start;
	for(i=0;i<list->size;i++)
	{
		printf("%d ",*(int*)(curr->data));
		curr = curr->next;
	}
    printf("\n");
}
