#include <stdlib.h>

#include "list.h"

struct _Node {
	ListValue val;
	Node* next;
	Node* prev;
};

struct _List {
	Node* head;
	
	unsigned size;

	Node* iter;
};

Node* 
new_node (ListValue val) {
	Node* n = (Node*)malloc(sizeof(Node));

	n->val = val;
	n->next = NULL;
	n->prev = NULL;

	return n;
}

ListValue 
node_value(Node* n)
{
	return n->val;
}

void 
node_delete (List* l, Node* n) {
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

List* 
new_list() {
	List* l = (List*) malloc(sizeof(List));

	l->head = NULL;
	l->size = 0;
	l->iter = NULL;

	return l;
}

void list_delete(List*);

void 
ls_insert(List* l, ListValue val) {
	Node* n = new_node(val);

	if (l->head != NULL) {
		l->head->prev = n;
		n->next = l->head;
	}

	l->head = n;
}

// set up list iterator. return the first node
Node* 
ls_iter(List* l) {
	l->iter = l->head;
	return l->iter;
}

bool 
ls_is_end (List* l) {
	return l->iter == NULL;
}

// next node 
Node* 
ls_next(List* l) {

	if (ls_is_end(l)) {
		return NULL;
	}

	l->iter = l->iter->next;
	return l->iter;
}

void 
ls_foreach (List* l, ListIterFunc func) {
	for (Node* n = ls_iter(l); !ls_is_end(l); n = ls_next(l))
	{
		(*func)(l, n);
	}
}

