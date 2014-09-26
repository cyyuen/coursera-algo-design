#include <stdio.h>
#include "partition.h"

const int N = 10000;

int A[N];

int comp_count = 0;

void swap(int* a, int *b) {
	if (a == b) {
		return;
	}
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int quick_sort_helper(int A[], int start, int end) {
	// if size is 1
	if (end - start <= 1) {
		return 0;
	}

	int i = pivot(A, start, end);
	int p = A[i];

	// place pivot to the first position
	swap( A + start, A +  i);

	i = start + 1;

	for (int j = i; j != end; ++j) {
		if (A[j] < p) {
			swap(A + i, A + j);
			i++;
		}
		comp_count++;
	}

	swap(A + start, A + i - 1);

	int lhs = quick_sort_helper(A, start, i - 1);
	int rhs = quick_sort_helper(A, i, end);

	return end - start - 1 + lhs + rhs;
}

int quick_sort(int A[], int size) {

	return quick_sort_helper(A, 0, size);
}

int main(int argc, char const *argv[])
{
	int tmp=0, i = 0;

	while(scanf("%d", &tmp) > 0){
		
		A[i++] = tmp;
	}

	int c = quick_sort(A, i);

	printf("%d\n", c);

	return 0;
}
