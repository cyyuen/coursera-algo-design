#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "randset.h"
#include "hashtbl.h"

struct randset_
{
	randset_t* buf;
	unsigned top;
	unsigned cap;

	// key position mapping
	hashtbl* kpmap;

	randset_keyfunc keyfunc;

	unsigned iter;
};

typedef struct{
	unsigned key;
	unsigned pos;
} kpmap;

static kpmap*
new_kpmap(unsigned key, unsigned pos)
{
	kpmap* m = malloc(sizeof(kpmap));
	
	m->key = key;
	m->pos = pos;

	return m;
}

static unsigned
kpmap_keyfunc (randset_t val) {
	return ((kpmap*)val)->key;
}

randset*
new_randset(unsigned cap, randset_keyfunc keyfunc)
{
	randset* s = malloc(sizeof(randset));
	s->cap = cap;

	s->buf = malloc(sizeof(randset_t) * s->cap);
	s->top = 0;

	s->kpmap = new_hashtbl(cap, &kpmap_keyfunc);

	s->keyfunc = keyfunc;

	s->iter = 0;

	return s;
}

unsigned
randset_size(randset* s) 
{
	return s->top;
}

static unsigned
randset_last(randset* s) {
	return randset_size(s) - 1;
}

bool 
randset_is_end(randset* s) 
{
	return s->iter == randset_size(s);
}

randset_t 
randset_iter(randset* s) 
{	
	s->iter = 0;

	return s->buf[s->iter];
};

randset_t 
randset_next(randset* s) 
{
	if (randset_is_end(s)) {
		return NULL;
	}

	s->iter = (s->iter) + 1;

	return s->buf[s->iter];
}

void
randset_mulpush(randset* s, randset_t val, int k) {
	unsigned key = (*s->keyfunc)(val);

	hashtbl_node* n = hashtbl_lookup(s->kpmap, key);

	// Not found. This is a new value
	if (n == NULL) {
		s->buf[s->top] = val;

		kpmap* m = new_kpmap(key, s->top);

		hashtbl_mulinsert(s->kpmap, m, k);

		s->top++;
	} else {
		hashtbl_mulinsert(s->kpmap, hashtbl_value(n), k);
	}
}

void
randset_push(randset* s, randset_t val) {
	randset_mulpush(s, val, 1);
}

randset_t
randset_get(randset* s, unsigned idx) {
	return s->buf[idx];
}

randset_t 
randset_pop_at(randset* s, unsigned idx) 
{
	if (idx > randset_last(s) || randset_size(s) == 0) {
		printf("index %u\n", idx);
		return NULL;
	}

	randset_t v = randset_get(s, idx);
	unsigned vkey = s->keyfunc(v);

	hashtbl_delete(s->kpmap,  vkey);

	if (idx != randset_last(s)) {

		// move the last element to the idx
		randset_t u = s->buf[randset_last(s)];

		s->buf[idx] = u;

		unsigned ukey = (*s->keyfunc)(u);

		hashtbl_node* htn = hashtbl_lookup(s->kpmap, ukey);

		((kpmap*)hashtbl_value(htn))->pos = idx;
	}
	
	s->top--;

	return v;
}

void
randset_remove(randset* s, randset_t ele) {
	unsigned key = (*s->keyfunc)(ele);

	hashtbl_node* n = hashtbl_lookup(s->kpmap, key);

	if (n == NULL) {
		return;
	}

	unsigned idx = ((kpmap*)hashtbl_value(n))->pos;
	
	randset_pop_at(s, idx);
}

randset_t
randset_pop(randset* s) {
	unsigned idx = rand() % randset_size(s);
	return randset_pop_at(s, idx);
}

int
randset_e_weight(randset* s, randset_t e) 
{
	unsigned key = (*s->keyfunc)(e);

	return hashtbl_weight(hashtbl_lookup(s->kpmap, key));
}

/*
 * This two randset must use the same keyfunc
 */
randset*
randset_merge(randset* v, randset* u) {
	// use randset v as based randset

	for (randset_t i = randset_iter(u); 
		 !randset_is_end(u); 
		 i = randset_next(u)) {

		randset_mulpush(v, i, randset_e_weight(u, i));
	}

	return v;
}

static void
randset_hashtbl_dump_helper(hashtbl_node* n) {
	kpmap* m = hashtbl_value(n);

	printf("(%u:%u)", m->pos, hashtbl_weight(n));
}

void randset_dump(randset* s) {
	
	printf("top:%u cap:%u\n", s->top, s->cap);

	printf("ids:");

	for (randset_t i = randset_iter(s); 
		 !randset_is_end(s); 
		 i = randset_next(s)) {
		printf("%d\t", (*(s->keyfunc))(i));
	}

	printf("\n");

	printf("\n");

	hashtbl_dump(s->kpmap, &randset_hashtbl_dump_helper);
	
}