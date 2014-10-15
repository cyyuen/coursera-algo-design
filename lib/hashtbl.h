#ifndef __PHI_HASHTBL_H__
#define __PHI_HASHTBL_H__

/**
 * Hash Table 
 * 
 * Use chaining implementation
 */
typedef struct hashtbl_node_ hashtbl_node;

typedef struct hashtbl_ hashtbl;

typedef void* hashtbl_t;

typedef unsigned (*hashtbl_keyfunc) (hashtbl_t);

typedef void (*hashtbl_dumpfunc) (hashtbl_node*);

hashtbl_t hashtbl_value(hashtbl_node*);

unsigned hashtbl_weight(hashtbl_node*);

/**
 * hash table creation
 */
hashtbl* new_hashtbl(unsigned cap, hashtbl_keyfunc keyfunc);

/**
 * insert. O(1)
 *
 * insert the new val to hash table
 * if the value is existed, increase the number of value by 1
 */
void hashtbl_insert(hashtbl* h, hashtbl_t val);

/**
 * insert. O(1)
 *
 * insert the new val to hash table multiple k times
 * if the value is existed, increase the number of value by 1
 */
void hashtbl_mulinsert(hashtbl* h, hashtbl_t val, unsigned k);

/**
 * delete. O(1)
 */
void hashtbl_delete(hashtbl* h, unsigned key);

/**
 * lookup. O(1)
 */
hashtbl_node* hashtbl_lookup(hashtbl* h, unsigned key);

void hashtbl_dump(hashtbl* h, hashtbl_dumpfunc dumpfunc);

#endif /* End of __PHI_HASHTBL_H__ */
