#include <stdio.h>
#include <string.h>

int merchants[300], N;
long long sum;

/* Codigo para calcular n sobre k.
 * Para que funcione, M > 1 */
#define MAX_N 300
#define MAX_K 300
long long M, binomial_cache[MAX_N+1][MAX_K+1];
static long long
binomial_coefficient(int n, int k)
{
	if(binomial_cache[n][k] != 0)
		return binomial_cache[n][k];
	if(k > n-k)
		k = n-k;
	if(k == 0 || n <= 1)
		return (binomial_cache[n][k] = 1);
	binomial_cache[n][k] = (binomial_coefficient(n-1, k) + binomial_coefficient(n-1, k-1)) % M;
	return binomial_cache[n][k];
}

/* i and prev start as 1. n starts as number of foreign merchants. N >= 2 */
static void
do_rec(int i, int n, int putmerchs, long long prev)
{
	int k, maxk, j;

	i = i+1;

	if(i == N) {
		sum = (sum + prev) % M;
		return;
	}

	maxk = i - merchants[N-i] - putmerchs;
	if(maxk > n) maxk = n;
	for(k=0; k<=maxk; k++) {
/*		for(j=1; j<i; j++)
			printf("   ");
		printf("%d %d\n", n, k); */

		do_rec(i, n-k, putmerchs+k, (prev * binomial_coefficient(n, k)) % M);
	}
}

int
main()
{
	int i, j, m, ncases, curcase;

	scanf("%d", &ncases);
	for(curcase=0; curcase<ncases; curcase++) {
		scanf("%d %d %lld", &N, &m, &M);
		if(N==1) {
			if(m==1)
				scanf("%*d %*d");
			sum = 1;
			goto YES;
		}

		memset(merchants, 0, 300*sizeof(int));
		for(i=0; i<m; i++) {
			scanf("%*d %d", &j);
			merchants[j-1]++;
		}
		
/*		for(i=0; i<N; i++)
			printf("%d ", merchants[i]);
		putchar('\n'); */

		if(merchants[N-1] > 1)
			goto NO;
		for(i=2; i<=N; i++) {
			merchants[N-i] += merchants[N-i+1];
			if(merchants[N-i] > i)
				goto NO;
		}

/*		for(i=0; i<N; i++)
			printf("%d ", merchants[i]);
		putchar('\n'); */

		sum = 0;
		do_rec(0, N-m, 0, 1);

YES:
		printf("YES %lld\n", sum);
		continue;
NO:
		puts("NO");
	}
	return 0;
}
