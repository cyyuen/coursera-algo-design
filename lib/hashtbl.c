#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"
#include "hashtbl.h"

/**
 * Hash Table 
 * 
 * Use chaining implementation
 */
struct hashtbl_node_
{
	// the content
	hashtbl_t val;

	unsigned key;

	// the number of the node. there're redundent nodes
	unsigned num;
};

struct hashtbl_
{
	unsigned cap;

	list** tbl;

	unsigned (*keyfunc) (void*);

};

hashtbl_t 
hashtbl_value(hashtbl_node* n) 
{
	return n->val;
}

unsigned 
hashtbl_weight(hashtbl_node* n) 
{
	return n->num;
}

hashtbl_node*
new_hashtbl_node(hashtbl_t val, unsigned key) 
{
	hashtbl_node* n = malloc(sizeof(hashtbl_node));

	n->val = val;
	n->key = key;
	n->num = 1;

	return n;
}

void
hashtbl_node_delete(hashtbl_node* n)
{
	free(n);
}

static unsigned
hashfunc(unsigned key, unsigned size)
{
	return key % size;
}

hashtbl* 
new_hashtbl(unsigned cap, hashtbl_keyfunc keyfunc)
{
	hashtbl* h = (hashtbl*)malloc(sizeof(hashtbl));
	
	h->cap = cap;
	h->keyfunc = keyfunc;
	h->tbl = malloc(sizeof(list*) * h->cap);
	memset(h->tbl, 0, sizeof(list*) * h->cap);

	return h;
}

hashtbl_node* 
hashtbl_lookup(hashtbl* h, unsigned key) 
{
	unsigned idx = hashfunc(key, h->cap);

	list* l = h->tbl[idx];

	if (l != NULL) {
		for (list_node* n = ls_iter(l); !ls_is_end(l); n = ls_next(l)) {

			if (key == ((hashtbl_node*)node_value(n))->key) {
				return node_value(n);
			}
		}
	}

	return NULL;
}

void 
hashtbl_mulinsert(hashtbl* h, hashtbl_t val, unsigned k)
{
	unsigned key = (*(h->keyfunc))(val);
	
	hashtbl_node* hn = hashtbl_lookup(h, key);

	if (hn != NULL) {
		hn->num += k;
		return;
	}

	unsigned idx = hashfunc(key, h->cap);

	hashtbl_node* n = new_hashtbl_node(val, key);
	n->num = k;

	if(h->tbl[idx] == NULL) {
		h->tbl[idx] = new_list();
	}

	ls_insert(h->tbl[idx], n);
}


void 
hashtbl_insert(hashtbl* h, hashtbl_t val)
{
	hashtbl_mulinsert(h, val, 1);
}

void 
hashtbl_delete(hashtbl* h, unsigned key) 
{
	unsigned idx = hashfunc(key, h->cap);

	list* l = h->tbl[idx];

	if (l != NULL) {

		for (list_node* n = ls_iter(l); !ls_is_end(l); n = ls_next(l)) {
			
			hashtbl_node* htn = node_value(n);

			if (key == htn->key) {
				node_delete(l, n);
				hashtbl_node_delete(htn);
				return;
			}
		}
	}
}

static
void builtin_dumpfunc(hashtbl_node* n)
{
	printf("(%u:%u) ", n->key, n->num);
}


void hashtbl_dump(hashtbl* h, hashtbl_dumpfunc dumpfunc)
{
	void (*func) (hashtbl_node*) = NULL;

	if (dumpfunc == NULL)
	{
		func = &builtin_dumpfunc;
	} else {
		func = dumpfunc;
	}

	for (int i = 0; i!=h->cap; ++i) {
		list* l = h->tbl[i];

		if (l!=NULL) {
			printf("%d: ", i);

			for (list_node* n = ls_iter(l); !ls_is_end(l); n = ls_next(l)) {
				(*func)((hashtbl_node*)node_value(n));
			}

			printf("\n");
		}
	}
}
