#include <stdio.h>
#include <limits.h>

#define OBJECTS 2000
#define DIVISORS 20

int cost[DIVISORS+1][OBJECTS];
int val[OBJECTS], sum[OBJECTS];

#define ROUND(n) ((mod=n%10) < 5 ? n-mod : n+10-mod)

int main() {
	int N, D, i, j, mod, k;
	while(scanf("%d %d", &N, &D) == 2) {
		scanf("%d", &val[0]);
		sum[0] = val[0];
		cost[0][0] = ROUND(sum[0]);
		for(i=1; i<N; i++) {
			scanf("%d", &val[i]);
			sum[i] = sum[i-1] + val[i];
			cost[0][i] = ROUND(sum[i]);
		}

		for(j=0; j<D; j++)
			cost[j][0] = cost[0][0];

		int total_min = cost[0][N-1];

		for(j=1; j<=D; j++) {
			for(i=1; i<N; i++) {
				int min = INT_MAX;
				for(k=i-1; k>=0; k--) {
					int s = sum[i] - sum[k];
					int v = cost[j-1][k] + ROUND(s);
					if(v < min) min = v;
				}
				cost[j][i] = min;
			}
			if(cost[j][N-1] < total_min)
				total_min = cost[j][N-1];
		}
#ifndef ONLINE_JUDGE
		for(j=0; j<=D; j++) {
			for(i=0; i<N; i++)
				printf("%d ", cost[j][i]);
			putchar('\n');
		}
#endif
		printf("%d\n", total_min);
	}
	return 0;
}
