typedef struct
{
	void** buf;
	unsigned top;
	unsigned cap;

	int* hashtbl;
	int* weight;
	int (*keyfunc)(void*);
} Stack;

Stack* new_stack(unsigned cap, int (*keyfunc)(void*));

unsigned stack_size(Stack* s);

void stack_push(Stack* s, void* val);

void stack_push_w(Stack* s, void* val, int w);

void* stack_get(Stack* s, unsigned idx);

void* stack_pop_at(Stack* s, unsigned idx);

void stack_remove(Stack* s, void* ele);

void* stack_pop(Stack* s);

void* stack_rand_pop(Stack* s);

void* stack_merge(Stack* v, Stack* u);

int stack_e_weight(Stack* s, void* e);

void stack_dump(Stack* s);