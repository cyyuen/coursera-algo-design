#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	void** buf;
	unsigned top;
	unsigned cap;

	int* hashtbl;
	int* weight;
	int (*keyfunc)(void*);
} Stack;

Stack*
new_stack(unsigned cap, int (*keyfunc)(void*)) {
	Stack* s = malloc(sizeof(Stack));
	s->cap = cap;

	s->buf = malloc(sizeof(void*) * s->cap);
	s->top = 0;

	s->hashtbl = malloc(sizeof(int) * s->cap);
	memset(s->hashtbl, -1, sizeof(int) * s->cap);

	s->weight = malloc(sizeof(int) * s->cap);
	memset(s->weight, 0, sizeof(int) * s->cap);

	s->keyfunc = keyfunc;

	return s;
}

unsigned
stack_size(Stack* s) {
	return s->top;
}

static int
keyhash(Stack* s, void* val) {
	return (*(s->keyfunc))(val) % s->cap;
}

void
stack_push_w(Stack* s, void* val, int w) {
	int key = keyhash(s, val);

	// new item
	if (s->weight[key] == 0) {
		s->buf[s->top] = val;
		s->hashtbl[key] = s->top;
		s->top++;
	}
	s->weight[key] += w;
}

void
stack_push(Stack* s, void* val) {
	stack_push_w(s, val, 1);
}

void*
stack_get(Stack* s, unsigned idx) {
	return s->buf[idx];
}

int
stack_last(Stack* s) {
	return stack_size(s) - 1;
}

void* 
stack_pop_at(Stack* s, unsigned idx) {
	if (idx > stack_last(s) || stack_size(s) == 0) {
		// printf("Opp: %d %d\n", idx, stack_size(s));
		return NULL;
	}

	//printf("p1\n");
	void* v = stack_get(s, idx);

	//printf("p2\n");
	// delete the idx of v
	int vkey = keyhash(s, v);
	s->hashtbl[vkey] = -1;
	s->weight[vkey] = 0;

	//printf("p3\n");
	if (idx != stack_last(s)) {
		
		//printf("%d %d\n", stack_size(s), idx);

		//printf("p3.1\n");
		// move the last element to the idx
		void* u = s->buf[stack_last(s)];
		
		//printf("p3.2\n");
		s->buf[idx] = u;

		//printf("p3.3\n");
		int ukey = keyhash(s, u);
		
		//printf("p3.4\n");
		s->hashtbl[ukey] = idx;
	}
	
	s->top--;

	//printf("p4\n");
	return v;
}

void
stack_remove(Stack* s, void* ele) {
	int key = keyhash(s, ele);
	int idx = s->hashtbl[key];

	if (idx != -1) {
		void* dum = stack_pop_at(s, idx);
	}
}

void*
stack_pop(Stack* s) {
	return stack_pop_at(s, stack_last(s));
}

void*
stack_rand_pop(Stack* s) {
	unsigned idx = rand() % stack_size(s);
	return stack_pop_at(s, idx);
}

/*
 * This two stack must use the same keyfunc
 */
void*
stack_merge(Stack* v, Stack* u) {
	// use stack v as based stack
	int usize = stack_size(u);

	for (int i = 0; i != usize; ++i) {
		// iterate each element in u's buf
		void* e = u->buf[i];

		int ekey = keyhash(v, e);

		stack_push_w(v, e, u->weight[ekey]);
	}

	return v;
}

int
stack_e_weight(Stack* s, void* e) {
	return s->weight[keyhash(s, e)];
}

void stack_dump(Stack* s) {
	/*
	printf("top:%u cap:%u\n", s->top, s->cap);

	printf("ids:");
	for (int i = 0; i < stack_size(s); ++i)
	{
		printf("%d\t", (*(s->keyfunc))(s->buf[i]));
	}
	printf("\n");

	printf("hst:");
	for (int i = 0; i < s->cap; ++i)
	{
		printf("%d\t", s->hashtbl[i]);
	}
	printf("\n");

	printf("wgh:");
	for (int i = 0; i < s->cap; ++i)
	{
		printf("%d\t", s->weight[i]);
	}
	printf("\n");
	printf("\n");
	*/
}