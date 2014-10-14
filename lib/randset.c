#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "randset.h"
#include "hashtbl.h"

struct _RandSet
{
	RandSetValue* buf;
	unsigned top;
	unsigned cap;

	// key position mapping
	Hashtbl* kpmap;

	RandSetKeyFunc keyfunc;

	unsigned iter;
};

typedef struct{
	unsigned key;
	unsigned pos;
} KPMap;

static KPMap*
new_kpmap(unsigned key, unsigned pos)
{
	KPMap* m = malloc(sizeof(KPMap));
	
	m->key = key;
	m->pos = pos;

	return m;
}

static unsigned
kpmap_keyfunc (RandSetValue val) {
	return ((KPMap*)val)->key;
}

RandSet*
new_randset(unsigned cap, RandSetKeyFunc keyfunc)
{
	RandSet* s = malloc(sizeof(RandSet));
	s->cap = cap;

	s->buf = malloc(sizeof(RandSetValue) * s->cap);
	s->top = 0;

	s->kpmap = new_hashtbl(cap, &kpmap_keyfunc);

	s->keyfunc = keyfunc;

	s->iter = 0;

	return s;
}

unsigned
randset_size(RandSet* s) 
{
	return s->top;
}

static unsigned
randset_last(RandSet* s) {
	return randset_size(s) - 1;
}

bool 
randset_is_end(RandSet* s) 
{
	return s->iter == randset_size(s);
}

RandSetValue 
randset_iter(RandSet* s) 
{	
	s->iter = 0;

	return s->buf[s->iter];
};

RandSetValue 
randset_next(RandSet* s) 
{
	if (randset_is_end(s)) {
		return NULL;
	}

	s->iter = (s->iter) + 1;

	return s->buf[s->iter];
}

void
randset_mulpush(RandSet* s, RandSetValue val, int k) {
	unsigned key = (*s->keyfunc)(val);

	HTNode* n = ht_lookup(s->kpmap, key);

	// Not found. This is a new value
	if (n == NULL) {
		s->buf[s->top] = val;

		KPMap* m = new_kpmap(key, s->top);

		ht_mulinsert(s->kpmap, m, k);

		s->top++;
	} else {
		ht_mulinsert(s->kpmap, ht_value(n), k);
	}
}

void
randset_push(RandSet* s, RandSetValue val) {
	randset_mulpush(s, val, 1);
}

RandSetValue
randset_get(RandSet* s, unsigned idx) {
	return s->buf[idx];
}

RandSetValue 
randset_pop_at(RandSet* s, unsigned idx) 
{
	if (idx > randset_last(s) || randset_size(s) == 0) {
		printf("index %u\n", idx);
		return NULL;
	}

	RandSetValue v = randset_get(s, idx);
	unsigned vkey = s->keyfunc(v);

	ht_delete(s->kpmap,  vkey);

	if (idx != randset_last(s)) {

		// move the last element to the idx
		RandSetValue u = s->buf[randset_last(s)];

		s->buf[idx] = u;

		unsigned ukey = (*s->keyfunc)(u);

		HTNode* htn = ht_lookup(s->kpmap, ukey);

		((KPMap*)ht_value(htn))->pos = idx;
	}
	
	s->top--;

	return v;
}

void
randset_remove(RandSet* s, RandSetValue ele) {
	unsigned key = (*s->keyfunc)(ele);

	HTNode* n = ht_lookup(s->kpmap, key);

	if (n == NULL) {
		return;
	}

	unsigned idx = ((KPMap*)ht_value(n))->pos;
	
	randset_pop_at(s, idx);
}

RandSetValue
randset_pop(RandSet* s) {
	unsigned idx = rand() % randset_size(s);
	return randset_pop_at(s, idx);
}

int
randset_e_weight(RandSet* s, RandSetValue e) 
{
	unsigned key = (*s->keyfunc)(e);

	return ht_weight(ht_lookup(s->kpmap, key));
}

/*
 * This two RandSet must use the same keyfunc
 */
RandSet*
randset_merge(RandSet* v, RandSet* u) {
	// use RandSet v as based RandSet

	for (RandSetValue i = randset_iter(u); 
		 !randset_is_end(u); 
		 i = randset_next(u)) {

		randset_mulpush(v, i, randset_e_weight(u, i));
	}

	return v;
}

static void
randset_ht_dump_helper(HTNode* n) {
	KPMap* m = ht_value(n);

	printf("(%u:%u)", m->pos, ht_weight(n));
}

void randset_dump(RandSet* s) {
	
	printf("top:%u cap:%u\n", s->top, s->cap);

	printf("ids:");

	for (RandSetValue i = randset_iter(s); 
		 !randset_is_end(s); 
		 i = randset_next(s)) {
		printf("%d\t", (*(s->keyfunc))(i));
	}

	printf("\n");

	printf("\n");

	ht_dump(s->kpmap, &randset_ht_dump_helper);
	
}