#include <stdio.h>

const unsigned int N = 100000;

unsigned int arr[N];
unsigned int buffer[N];

unsigned int count_inversion(unsigned int start, unsigned int end)
{

	if (start >= end) {
		return 0;
	}

	unsigned int mid = (start + end) / 2;
	unsigned int lhs_count = count_inversion(start, mid);
	unsigned int rhs_count = count_inversion(mid+1, end);
	unsigned int cross_count = 0;

	unsigned int i = start, j = mid + 1, k = start, base = 0;

	while (k <= end){

		// j reach the end
		if (j > end && i <= mid) {
			while (i<=mid){
				buffer[k] = arr[i];
				cross_count += (j - mid - 1);
				k++;
				i++;
			}
			break;
		}

		// i reach the end
		else if (i > mid && j <= end) {
			while (j <= end){
				buffer[k] = arr[j];
				k++;
				j++;
			}
			break;
		}
		else if (arr[i] < arr[j]) {
			buffer[k] = arr[i];
			cross_count += (j - mid - 1);
			i++;
		} else {
			buffer[k] = arr[j];
			j++;
		}
		k++;
	}

	for (unsigned int z = start; z <= end; z++) {
		arr[z] = buffer[z];
	}

	return lhs_count + rhs_count + cross_count;
}

int main(int argc, char const *argv[])
{
	unsigned int i = 0, k = 0;
	while(scanf("%u", &k) > 0) {
		arr[i] = k;
		i++;
	}

	unsigned int c = count_inversion(0, i-1);

	printf("%u\n", c);

	return 0;
}
