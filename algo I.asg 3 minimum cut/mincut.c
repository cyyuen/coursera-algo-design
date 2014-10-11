#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "../lib/stack.h"

const int N = 205;
const int L = 10000;
const char* D = " \t\n";

typedef struct{
	int id;
	Stack* adjc;
} Vertex;

int
vertex_id(void* v) {
	return ((Vertex*)v)->id;
}

void
add_adjc(Vertex* v, Vertex* u) {
	stack_push(v->adjc, (void*)u);
}

// vertex* array A is also a random set
int DATA[N][N];
Vertex** A;
Stack* V;

int size = 0;

Vertex*
get_vertex(int index) {
	if (A[index] == NULL) {

		Vertex* v = (Vertex*) malloc(sizeof(Vertex));

		v->id = index;
		v->adjc = new_stack(N, &vertex_id);

		stack_push(V, v);

		A[index] = v;

		if (index > size)
			size = index;
	}

	return A[index];
}


char*
inttok(char * str, int * i, const char * delimiters) {

	char* tok = strtok (str, delimiters);

	if (tok == NULL || isspace(tok[0])) {
		return NULL;
	}
	
	*i = atoi(tok);
	
	return tok;
}

Vertex* 
vertex_merge(Vertex* v, Vertex* u) {

	v->adjc = stack_merge(v->adjc, u->adjc);

	stack_remove(v->adjc, v);

	int size = stack_size(v->adjc);

	for (int i = 0; i!=size; ++i) {
		Vertex* e = v->adjc->buf[i];

		stack_remove(e->adjc, v);

		stack_remove(e->adjc, u);

		stack_push_w(e->adjc, v, stack_e_weight(v->adjc, e));
	}

	return v;
}

int random_contrat() {
	Vertex *v, *u;

	while(stack_size(V) > 2) {
		// randomly choose an edges
		v = (Vertex*)stack_rand_pop(V);
		u = (Vertex*)stack_rand_pop(v->adjc);

		stack_dump(V);

		stack_remove(V, u);

		Vertex* w = vertex_merge(v, u);

		stack_push(V, w);
	}

	v = (Vertex*)stack_rand_pop(V);
	u = (Vertex*)stack_rand_pop(V);

	return stack_e_weight(v->adjc, u);
}

int do_contract(int num_of_n) {
	A = malloc(sizeof(Vertex*) * N);
	V = new_stack(N, &vertex_id);

	for (int i = 0; i < num_of_n; ++i)
	{
		int num_ajdc = DATA[i][0];
		Vertex* v = get_vertex(i);

		for (int j = 0; j < num_ajdc; ++j)
		{
			int uid = DATA[i][j+1];

			Vertex* u = get_vertex(uid);
			add_adjc(v, u);

		}

	}

	return random_contrat();
}


int main(int argc, char const *argv[])
{
	//V = new_stack(N, &vertex_id);
	memset(DATA, 0, N*N);

	char line[L];

	int s = 0;

	time_t t;
   
   	/* Intializes random number generator */
   	srand((unsigned) time(&t));

	while(!feof(stdin)) {
		
		fgets(line, L, stdin);

		int vid = 0, adjc = 0;

		inttok(line, &vid, D);

		int num_adjc = 0;
		int start_p = 1;

		while(inttok(NULL, &adjc, D) != NULL) {
			DATA[vid-1][start_p] = adjc-1;
			start_p++;
			num_adjc++;
		}
		DATA[vid-1][0] = num_adjc;

		s++;
	}

	int num_of_n = s;

	int i = do_contract(num_of_n);
	
	s = s*s;

	while(s != 0) {
		s--;

		int j = do_contract(num_of_n);

		if (j < i) {
			i = j;
		}
	}

	printf("%d\n", i);
	
	return 0;
}