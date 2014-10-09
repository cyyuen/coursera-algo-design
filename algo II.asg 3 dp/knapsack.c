#include <stdio.h>
#include <string.h>

const int MAXCAP = 100000000;

int A[2][MAXCAP];

int prev(int i) {
	return i == 0? 1 : 0;
}

int next(int i) {
	return i == 0? 1 : 0;
}

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

	memset(A, 0, 2 * MAXCAP);

	int v, w;

	int idx = 0;

	for (int i = 0; i != size; ++i) {
		
		scanf("%u %u", &v, &w);

		for(int j = 1; j <= cap; ++j) {

			int up = prev(idx);

			int v1, v2;

			v1 = A[up][j];

			if (j-w < 1) {
				v2 = 0;
			} else {
				v2 = A[up][j-w] + v;
			}

			A[idx][j] = max(v1, v2);
		}
		
		idx = next(idx);
	}

	printf("%u\n", A[prev(idx)][cap]);
	
	return 0;
}