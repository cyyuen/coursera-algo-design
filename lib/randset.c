#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <phi/randset.h>
#include <phi/list.h>

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
kpmap_keyfunc (void* val) {
	return ((KPMap*)val)->key;
}

RandSet*
new_randset(unsigned cap, unsigned (*keyfunc)(void*))
{
	RandSet* s = malloc(sizeof(RandSet));
	s->cap = cap;

	s->buf = malloc(sizeof(void*) * s->cap);
	s->top = 0;

	s->kpmap = new_hashtbl(cap, &kpmap_keyfunc);

	s->keyfunc = keyfunc;

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

void
randset_mulpush(RandSet* s, void* val, int k) {
	unsigned key = (*s->keyfunc)(val);

	HTNode* n = ht_lookup(s->kpmap, key);

	// Not found. This is a new value
	if (n == NULL) {
		s->buf[s->top] = val;

		KPMap* m = new_kpmap(key, s->top);

		ht_mulinsert(s->kpmap, m, k);

		s->top++;
	} else {
		n->num += k;
	}
}

void
randset_push(RandSet* s, void* val) {
	randset_mulpush(s, val, 1);
}

void*
randset_get(RandSet* s, unsigned idx) {
	return s->buf[idx];
}

void* 
randset_pop_at(RandSet* s, unsigned idx) 
{
	if (idx > randset_last(s) || randset_size(s) == 0) {
		printf("index %u\n", idx);
		return NULL;
	}

	void* v = randset_get(s, idx);
	unsigned vkey = s->keyfunc(v);

	ht_delete(s->kpmap,  vkey);

	if (idx != randset_last(s)) {

		// move the last element to the idx
		void* u = s->buf[randset_last(s)];

		s->buf[idx] = u;

		unsigned ukey = (*s->keyfunc)(u);

		HTNode* htn = ht_lookup(s->kpmap, ukey);

		((KPMap*)htn->val)->pos = idx;
	}
	
	s->top--;

	return v;
}

void
randset_remove(RandSet* s, void* ele) {
	unsigned key = (*s->keyfunc)(ele);

	HTNode* n = ht_lookup(s->kpmap, key);

	if (n == NULL) {
		return;
	}

	unsigned idx = ((KPMap*)n->val)->pos;
	
	randset_pop_at(s, idx);
}

void*
randset_pop(RandSet* s) {
	unsigned idx = rand() % randset_size(s);
	return randset_pop_at(s, idx);
}

int
randset_e_weight(RandSet* s, void* e) 
{
	unsigned key = (*s->keyfunc)(e);

	return (ht_lookup(s->kpmap, key))->num;
}

/*
 * This two RandSet must use the same keyfunc
 */
void*
randset_merge(RandSet* v, RandSet* u) {
	// use RandSet v as based RandSet
	int usize = randset_size(u);

	for (int i = 0; i != usize; ++i) {
		// iterate each element in u's buf
		void* e = u->buf[i];

		randset_mulpush(v, e, randset_e_weight(u, e));
	}

	return v;
}

static void
randset_ht_dump_helper(HTNode* n) {
	KPMap* m = n->val;

	printf("(%u:%u)", m->pos, n->num);
}

void randset_dump(RandSet* s) {
	
	printf("top:%u cap:%u\n", s->top, s->cap);

	printf("ids:");
	for (int i = 0; i < randset_size(s); ++i)
	{
		printf("%d\t", (*(s->keyfunc))(s->buf[i]));
	}
	printf("\n");

	ht_dump(s->kpmap, &randset_ht_dump_helper);
	
}