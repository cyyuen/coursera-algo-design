#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include <phi/randset.h>

const int N = 205;
const int L = 10000;
const char* D = " \t\n";

typedef struct{
	unsigned id;
	RandSet* adjc;
} Vertex;

unsigned
vertex_id(void* v) {
	return ((Vertex*)v)->id;
}

void
add_adjc(Vertex* v, Vertex* u) {
	randset_push(v->adjc, (void*)u);
}

// vertex* array A is also a random set
unsigned DATA[N][N];
Vertex** A;
RandSet* V;

int size = 0;

Vertex*
get_vertex(unsigned index) {
	if (A[index] == NULL) {

		Vertex* v = (Vertex*) malloc(sizeof(Vertex));

		v->id = index;
		v->adjc = new_randset(N, &vertex_id);

		randset_push(V, v);

		A[index] = v;

		if (index > size)
			size = index;
	}

	return A[index];
}


char*
inttok(char * str, unsigned * i, const char * delimiters) {

	char* tok = strtok (str, delimiters);

	if (tok == NULL || isspace(tok[0])) {
		return NULL;
	}
	
	*i = (unsigned)atoi(tok);
	
	return tok;
}

Vertex* 
vertex_merge(Vertex* v, Vertex* u) {

	v->adjc = randset_merge(v->adjc, u->adjc);

	randset_remove(v->adjc, v);

	for (Vertex* i = randset_iter(v->adjc); 
		 !randset_is_end(v->adjc);
		 i = randset_next(v->adjc))
	{
		randset_remove(i->adjc, v);

		randset_remove(i->adjc, u);

		randset_mulpush(i->adjc, v, randset_e_weight(v->adjc, i));
	}

	return v;
}

int random_contrat() {

	Vertex *v, *u;

	while(randset_size(V) > 2) {

		v = (Vertex*)randset_pop(V);

		u = (Vertex*)randset_pop(v->adjc);

		randset_remove(V, u);

		Vertex* w = vertex_merge(v, u);

		randset_push(V, w);
	}

	v = (Vertex*)randset_pop(V);
	u = (Vertex*)randset_pop(V);

	return randset_e_weight(v->adjc, u);
}

int do_contract(int num_of_n) {
	A = malloc(sizeof(Vertex*) * N);
	V = new_randset(N, &vertex_id);

	for (unsigned i = 0; i < num_of_n; ++i)
	{
		int num_ajdc = DATA[i][0];
		Vertex* v = get_vertex(i);

		for (unsigned j = 0; j < num_ajdc; ++j)
		{
			unsigned uid = DATA[i][j+1];

			Vertex* u = get_vertex(uid);
			add_adjc(v, u);
		}
	}

	return random_contrat();
}


int main(int argc, char const *argv[])
{
	//V = new_randset(N, &vertex_id);
	memset(DATA, 0, N*N);

	char line[L];

	int s = 0;

	time_t t;
   
   	/* Intializes random number generator */
   	srand((unsigned) time(&t));

   	/**
   		Store the data for multiple random contraction
   	 */
	while(!feof(stdin)) {
		
		fgets(line, L, stdin);

		unsigned vid = 0, adjc = 0;

		inttok(line, &vid, D);

		unsigned num_adjc = 0;
		unsigned start_p = 1;

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