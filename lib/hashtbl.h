#ifndef PHI_HASHTBL_H
#define PHI_HASHTBL_H

/**
 * Hash Table 
 * 
 * Use chaining implementation
 */
typedef struct _HTNode HTNode;

typedef struct _Hashtbl Hashtbl;

typedef void* HashtblValue;

typedef unsigned (*HashtblKeyFunc) (HashtblValue);

typedef void (*HashtblDumpFunc) (HTNode*);

HashtblValue ht_value(HTNode*);

unsigned ht_weight(HTNode*);

/**
 * hash table creation
 */
Hashtbl* new_hashtbl(unsigned cap, HashtblKeyFunc keyfunc);

/**
 * insert. O(1)
 *
 * insert the new val to hash table
 * if the value is existed, increase the number of value by 1
 */
void ht_insert(Hashtbl* h, HashtblValue val);

/**
 * insert. O(1)
 *
 * insert the new val to hash table multiple k times
 * if the value is existed, increase the number of value by 1
 */
void ht_mulinsert(Hashtbl* h, HashtblValue val, unsigned k);

/**
 * delete. O(1)
 */
void ht_delete(Hashtbl* h, unsigned key);

/**
 * lookup. O(1)
 */
HTNode* ht_lookup(Hashtbl* h, unsigned key);

void ht_dump(Hashtbl* h, HashtblDumpFunc dumpfunc);

#endif /* End of PHI_HASHTBL_H */
