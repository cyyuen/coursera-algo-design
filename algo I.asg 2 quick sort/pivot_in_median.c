int pivot(int A[], int start, int end) {

	end = end - 1;

	int mid = (start + end) / 2;

	int s = A[start];
	int m = A[mid];
	int e = A[end];

	if ((s <= m && m <= e) || (e <= m && m <= s)) {
		return mid;
	} else if ((m <= s && s <= e) || (e <= s && s <= m)) {
		return start;
	} else if ((s <= e && e <= m) || (m <= e && e <= s)) {
		return end;
	} else {
		return -1;
	}
}