#ifndef PHI_LIST_H
#define PHI_LIST_H

#include <stdbool.h>

typedef struct Node
{
	void* val;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct {
	Node* head;
	
	unsigned size;

	Node* iter;
} List;

Node* new_node(void* val);

void node_delete (List* l, Node* n);

List* new_list();

void list_delete(List*);

void ls_insert(List*, void* val);

// set up list iterator. return the first node
Node* ls_iter(List*);

// next node 
Node* ls_next(List*);

// previous node
Node* ls_prev(List*);

bool ls_is_end(List*);

void ls_foreach (List* l, void (*func)(List*, Node*));

#endif /* End of PHI_LIST_H */