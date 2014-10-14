#ifndef PHI_LIST_H
#define PHI_LIST_H

#include <stdbool.h>

typedef void* ListValue;

typedef struct _Node Node;

typedef struct _List List;

typedef void (*ListIterFunc) (List*, Node*);

Node* new_node(ListValue val);

ListValue node_value(Node*);

void node_delete (List* l, Node* n);

List* new_list();

void list_delete(List*);

void ls_insert(List*, ListValue val);

// set up list iterator. return the first node
Node* ls_iter(List*);

// next node 
Node* ls_next(List*);

// previous node
Node* ls_prev(List*);

bool ls_is_end(List*);

void ls_foreach (List* l, ListIterFunc func);

#endif /* End of PHI_LIST_H */