#ifndef PHI_HASHTBL_H
#define PHI_HASHTBL_H

#include "list.h"

/**
 * Hash Table 
 * 
 * Use chaining implementation
 */
typedef struct
{
	// the content
	void* val;

	unsigned key;

	// the number of the node. there're redundent nodes
	unsigned num;

} HTNode;

typedef struct
{
	unsigned cap;

	List** tbl;

	unsigned (*keyfunc) (void*);

} Hashtbl;

/**
 * hash table creation
 */
Hashtbl* new_hashtbl(unsigned cap, unsigned (*keyfunc) (void*));

/**
 * insert. O(1)
 *
 * insert the new val to hash table
 * if the value is existed, increase the number of value by 1
 */
void ht_insert(Hashtbl* h, void* val);

/**
 * insert. O(1)
 *
 * insert the new val to hash table multiple k times
 * if the value is existed, increase the number of value by 1
 */
void ht_mulinsert(Hashtbl* h, void* val, unsigned k);

/**
 * delete. O(1)
 */
void ht_delete(Hashtbl* h, unsigned key);

/**
 * lookup. O(1)
 */
HTNode* ht_lookup(Hashtbl* h, unsigned key);

void ht_dump(Hashtbl* h, void (*dumpfunc)(HTNode*));

#endif /* End of PHI_HASHTBL_H */
