#include <stdio.h>
#include <string.h>

const int MAXCAP = 100000000;

int A[MAXCAP];

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int main(int argc, char const *argv[])
{

	int cap, size;

	scanf("%u %u", &cap, &size);

	memset(A, 0, MAXCAP);

	int v, w;

	int idx = 0;

	for (int i = 0; i != size; ++i) {
		
		scanf("%u %u", &v, &w);

		for(int j = cap; j > w; --j) {
			int v1, v2;

			A[j] = max(A[j], A[j-w] + v);
		}
	}

	printf("%u\n", A[cap]);
	
	return 0;
}