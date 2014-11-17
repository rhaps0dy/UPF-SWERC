#include <stdio.h>
#include <string.h>

int merchants[300], N;

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

long long ncombs[301][301];
static long long
calc(int n)
{
	int i, j, k;

	ncombs[1][n] = binomial_coefficient(n, 0);
	if(merchants[N-1] == 1) {
		ncombs[1][n-1] = 0;
	} else {
		ncombs[1][n-2] = 0;
		ncombs[1][n-1] = binomial_coefficient(n, 1);
	}
	for(i=2; i<N; i++) {
		for(j=n; n-j<=merchants[N-i]-i; j--) {
			ncombs[i][j] = 0;
			for(k=n; k>=j; k--) {
				ncombs[i][j] = (ncombs[i][j] + (binomial_coefficient(k, k-j)*ncombs[i-1][k]) % M) % M;
			}
		}
	}
	for(i=1; i<N; i++) {
		for(j=0; j<=n; j++)
			printf("%lld ", ncombs[i][j]);
		putchar('\n');
	}
	putchar('\n');
	return 0;
}

int
main()
{
	int i, j, m, ncases, curcase;
	long long sum;

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

		if(merchants[N-1] > 1)
			goto NO;
		for(i=2; i<=N; i++) {
			merchants[N-i] += merchants[N-i+1];
			if(merchants[N-i] > i)
				goto NO;
		}

		sum = calc(N-m);

YES:
		printf("YES %lld\n", sum);
		continue;
NO:
		puts("NO");
	}
	return 0;
}
