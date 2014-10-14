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
struct _HTNode
{
	// the content
	HashtblValue val;

	unsigned key;

	// the number of the node. there're redundent nodes
	unsigned num;
};

struct _Hashtbl
{
	unsigned cap;

	List** tbl;

	unsigned (*keyfunc) (void*);

};

HashtblValue 
ht_value(HTNode* n) 
{
	return n->val;
}

unsigned 
ht_weight(HTNode* n) 
{
	return n->num;
}

HTNode*
new_htnode(HashtblValue val, unsigned key) 
{
	HTNode* n = malloc(sizeof(HTNode));

	n->val = val;
	n->key = key;
	n->num = 1;

	return n;
}

void
htnode_delete(HTNode* n)
{
	free(n);
}

static unsigned
hashfunc(unsigned key, unsigned size)
{
	return key % size;
}

Hashtbl* 
new_hashtbl(unsigned cap, HashtblKeyFunc keyfunc)
{
	Hashtbl* h = (Hashtbl*)malloc(sizeof(Hashtbl));
	
	h->cap = cap;
	h->keyfunc = keyfunc;
	h->tbl = malloc(sizeof(List*) * h->cap);
	memset(h->tbl, 0, sizeof(List*) * h->cap);

	return h;
}

HTNode* 
ht_lookup(Hashtbl* h, unsigned key) 
{
	unsigned idx = hashfunc(key, h->cap);

	List* l = h->tbl[idx];

	if (l != NULL) {
		for (Node* n = ls_iter(l); !ls_is_end(l); n = ls_next(l)) {

			if (key == ((HTNode*)node_value(n))->key) {
				return node_value(n);
			}
		}
	}

	return NULL;
}

void 
ht_mulinsert(Hashtbl* h, HashtblValue val, unsigned k)
{
	unsigned key = (*(h->keyfunc))(val);
	
	HTNode* hn = ht_lookup(h, key);

	if (hn != NULL) {
		hn->num += k;
		return;
	}

	unsigned idx = hashfunc(key, h->cap);

	HTNode* n = new_htnode(val, key);
	n->num = k;

	if(h->tbl[idx] == NULL) {
		h->tbl[idx] = new_list();
	}

	ls_insert(h->tbl[idx], n);
}


void 
ht_insert(Hashtbl* h, HashtblValue val)
{
	ht_mulinsert(h, val, 1);
}

void 
ht_delete(Hashtbl* h, unsigned key) 
{
	unsigned idx = hashfunc(key, h->cap);

	List* l = h->tbl[idx];

	if (l != NULL) {

		for (Node* n = ls_iter(l); !ls_is_end(l); n = ls_next(l)) {
			
			HTNode* htn = node_value(n);

			if (key == htn->key) {
				node_delete(l, n);
				htnode_delete(htn);
				return;
			}
		}
	}
}

static
void builtin_dumpfunc(HTNode* n)
{
	printf("(%u:%u) ", n->key, n->num);
}


void ht_dump(Hashtbl* h, HashtblDumpFunc dumpfunc)
{
	void (*func) (HTNode*) = NULL;

	if (dumpfunc == NULL)
	{
		func = &builtin_dumpfunc;
	} else {
		func = dumpfunc;
	}

	for (int i = 0; i!=h->cap; ++i) {
		List* l = h->tbl[i];

		if (l!=NULL) {
			printf("%d: ", i);

			for (Node* n = ls_iter(l); !ls_is_end(l); n = ls_next(l)) {
				(*func)((HTNode*)node_value(n));
			}

			printf("\n");
		}
	}
}
