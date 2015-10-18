#include <stdio.h>
#include <string.h>

int cost[101];

int main() {
	int n, k, i, c, total;

	while(scanf("%d %d", &n, &k) == 2) {
		memset(cost, 0, sizeof(cost));
		k = n/k;
		total=0;
		for(i=0; i<n; i++) {
			scanf("%d", &c);
			if(cost[c] < k)
				cost[c]++;
			else
				total++;
		}
		printf("%d\n", total);
	}
	return 0;
}
