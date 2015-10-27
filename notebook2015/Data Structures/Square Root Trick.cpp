/* Partitions an array in sqrt(n) blocks of size sqrt(n) to support
 * O(sqrt(n)) range sum queries, O(sqrt(n)) range sum updates, and O(1)
 * point updates */
void update(LL *S, LL *A, int i, int k, int x) {
    S[i/k] = S[i/k] - A[i] + x;
    A[i] = x;
}

LL query(LL *S, LL *A, int lo, int hi, int k) {
	int sum=0, i=lo;
	while((i+1)%k != 0 && i <= hi)
		sum += A[i++];
	while(i+k <= hi)
		sum += S[i/k], i += k;
	while(i <= hi)
		sum += A[i++];
	return sum;
}
