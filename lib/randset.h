#ifndef PHI_RANDSET_H
#define PHI_RANDSET_H

#include <stdbool.h>

typedef struct _RandSet RandSet;

typedef void* RandSetValue;

typedef unsigned (*RandSetKeyFunc) (RandSetValue);

RandSet* new_randset(unsigned cap, RandSetKeyFunc);

unsigned randset_size(RandSet* s);

void randset_mulpush(RandSet* s, RandSetValue val, int k);

void randset_push(RandSet* s, RandSetValue val);

void randset_remove(RandSet* s, RandSetValue val);

RandSetValue randset_pop(RandSet* s);

int randset_e_weight(RandSet* s, RandSetValue val);

/*
 * These two RandSet must use the same keyfunc
 */
RandSet* randset_merge(RandSet* v, RandSet* u);

void randset_dump(RandSet* s);

RandSetValue randset_iter(RandSet* s);

RandSetValue randset_next(RandSet* s);

bool randset_is_end(RandSet* s);

#endif /* End of PHI_RANDSET_H */