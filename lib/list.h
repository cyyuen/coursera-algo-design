#ifndef __PHI_LIST_H__
#define __PHI_LIST_H__

#include <stdbool.h>

typedef void* list_node_t;

typedef unsigned list_size_t;

typedef struct list_node_ list_node;

typedef struct list_ list;

typedef void (*list_iter_func_t) (list*, list_node*);

list_node* new_node(list_node_t val);

list_node_t node_value(list_node*);

void node_delete (list* l, list_node* n);

list* new_list();

void list_delete(list*);

void ls_insert(list*, list_node_t val);

// set up list iterator. return the first node
list_node* ls_iter(list*);

// next node 
list_node* ls_next(list*);

// previous node
list_node* ls_prev(list*);

bool ls_is_end(list*);

void ls_foreach (list* l, list_iter_func_t func);

#endif /* End of __PHI_LIST_H__ */