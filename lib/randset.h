#ifndef PHI_RANDSET_H
#define PHI_RANDSET_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hashtbl.h"

typedef struct
{
	void** buf;
	unsigned top;
	unsigned cap;

	// key position mapping
	Hashtbl* kpmap;

	unsigned (*keyfunc) (void*);

} RandSet;

RandSet*
new_randset(unsigned cap, unsigned (*keyfunc)(void*));

unsigned
randset_size(RandSet* s);

void
randset_mulpush(RandSet* s, void* val, int k);

void
randset_push(RandSet* s, void* val);

void
randset_remove(RandSet* s, void* ele);

void*
randset_pop(RandSet* s);

int
randset_e_weight(RandSet* s, void* e);

/*
 * These two RandSet must use the same keyfunc
 */
void* randset_merge(RandSet* v, RandSet* u);

void randset_dump(RandSet* s);

#endif /* End of PHI_RANDSET_H */