#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste simplu inlantuite, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct LinkedList *list) {
    /* TODO */
    list->head=NULL;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct LinkedList *list, int n, void *new_data) {
    /* TODO */
    int i=0;
    struct Node *new,*curr;
    if(n<0  || list == NULL)
    	return;
    new=(struct Node*)malloc(sizeof(struct Node));
    if(n == 0 || list->head == NULL)
    {
    	new->next = list->head;
    	list->head = new;
    	new->data = new_data;
    }
    else
    {
    	curr = list->head;
    	while(i < n && curr->next != NULL)
    	{
    		i++;
    		curr = curr->next;
    	}
    	if(curr->next != NULL)
    	{
    		new->next = curr->next;
    		curr->next = new;
    		new->data = new_data;
    	}
    	else
    	{
    		new->next = NULL;
    		curr->next = new;
    		new->data = new_data;
    	}
    }
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1,
 * se elimina nodul de la finalul listei. Daca n < 0, eroare.
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct LinkedList *list, int n) {
    /* TODO */
    int i=0;
    struct Node *curr,*prev;
    if(list == NULL || list->head == NULL || n < 0)
    	exit(0);
    if(n == 0)
    {
    	curr = list->head;
    	list->head = curr->next;
    }
    else
    {
    	curr = list->head->next;
    	prev = list->head;
    	while(i < n-1 && curr->next != NULL)
    	{
    		i++;
    		prev = curr;
    		curr = curr->next;
    	}
    	if(curr->next != NULL)
    		prev->next = curr->next;
	    else
	    	prev->next = NULL;
	}
    return curr;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct LinkedList *list) {
    /* TODO */
    int n=1;
    struct Node *curr;
    if(list->head == NULL)
    	return 1;
    curr = list->head;
    while(curr->next != NULL)
    {
    	n++;
    	curr = curr->next;
    }
    return n;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista si actualizeaza la NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void free_list(struct LinkedList **list) {
    /* TODO */
    struct Node *curr,*prev;
    if(*list == NULL)
    	return;
    curr = (*list)->head;
    while(curr != NULL)
    {
    	prev = curr;
    	curr = curr->next;
    	free(prev);
    }
    free(*list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista inlantuita separate printr-un spatiu.
 */
void print_int_linkedlist(struct LinkedList *list) {
    /* TODO */
	struct Node *curr;
	curr = list->head;
	while(curr != NULL)
	{
		printf("%d ",*((int*)(curr->data)));
		curr = curr->next;
	}
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista inlantuita, separate printr-un spatiu.
 */
void print_string_linkedlist(struct LinkedList *list) {
    /* TODO */
    struct Node *curr;
    curr = list->head;
    while(curr != NULL)
    {
    	printf("%s ",(char*)(curr->data));
    	curr = curr->next;
    }
    printf("\n");
}
