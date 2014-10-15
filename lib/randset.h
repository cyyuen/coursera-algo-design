#ifndef __PHI_randset_H__
#define __PHI_randset_H__

#include <stdbool.h>

typedef struct randset_ randset;

typedef void* randset_t;

typedef unsigned (*randset_keyfunc) (randset_t);

randset* new_randset(unsigned cap, randset_keyfunc);

unsigned randset_size(randset* s);

void randset_mulpush(randset* s, randset_t val, int k);

void randset_push(randset* s, randset_t val);

void randset_remove(randset* s, randset_t val);

randset_t randset_pop(randset* s);

int randset_e_weight(randset* s, randset_t val);

/*
 * These two randset must use the same keyfunc
 */
randset* randset_merge(randset* v, randset* u);

void randset_dump(randset* s);

randset_t randset_iter(randset* s);

randset_t randset_next(randset* s);

bool randset_is_end(randset* s);

#endif /* End of __PHI_randset_H__ */