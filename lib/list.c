#include <stdlib.h>

#include "list.h"

struct list_node_ {
	list_node_t val;
	list_node* next;
	list_node* prev;
};

struct list_ {
	list_node* head;
	list_size_t size;
	list_node* iter;
};

list_node* 
new_node (list_node_t val) {
	list_node* n = (list_node*)malloc(sizeof(list_node));

	n->val = val;
	n->next = NULL;
	n->prev = NULL;

	return n;
}

inline list_node_t 
node_value(list_node* n)
{
	return n->val;
}

void 
node_delete (list* l, list_node* n) {
	if (n->next != NULL) {
		n->next->prev = n->prev;
	}

	if (n->prev != NULL) {
		n->prev->next = n->next;
	}

	if (l->head == n) {
		l->head = n->next;
	}

	free(n);
}

list* 
new_list() {
	list* l = (list*) malloc(sizeof(list));

	l->head = NULL;
	l->size = 0;
	l->iter = NULL;

	return l;
}

void 
ls_foreach (list* l, list_iter_func_t func) {
	for (list_node* n = ls_iter(l); !ls_is_end(l); n = ls_next(l))
	{
		(*func)(l, n);
	}
}

void 
list_delete(list* l)
{
	ls_foreach(l, &node_delete);
	free(l);
}

void 
ls_insert(list* l, list_node_t val) {
	list_node* n = new_node(val);

	if (l->head != NULL) {
		l->head->prev = n;
		n->next = l->head;
	}

	l->head = n;
}

// set up list iterator. return the first node
inline list_node* 
ls_iter(list* l) {
	l->iter = l->head;
	return l->iter;
}

inline bool 
ls_is_end (list* l) {
	return l->iter == NULL;
}

// next node 
inline list_node* 
ls_next(list* l) {

	if (ls_is_end(l)) {
		return NULL;
	}

	l->iter = l->iter->next;
	return l->iter;
}

