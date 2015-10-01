#include <stdio.h>
#include <string.h>

typedef long long LI;

#define DIM 20

LI values[DIM][DIM][DIM];
LI aux2[DIM][DIM];
LI aux[DIM];

int main() {
	int A, B, C, Ncases, i, j, k, l, m;

	scanf("%d", &Ncases);
	while(Ncases--) {
		scanf("%d %d %d", &A, &B, &C);
		for(i=0; i<A; i++)
			for(j=0; j<B; j++)
				for(k=0; k<C; k++)
					scanf("%lld", &values[i][j][k]);

		LI max = values[0][0][0];
		/* take all the possible horizontal cuts of the box and sum them vertically */
		for(i=0; i<A; i++) {
			memset(aux2, 0, sizeof(aux2));
			for(l=i; l<A; l++) {
				for(j=0; j<B; j++)
					for(k=0; k<C; k++)
						aux2[j][k] += values[l][j][k];
				/* Take all possible horizontal cuts of the summed plane and sum them vertically */
				for(j=0; j<B; j++) {
					memset(aux, 0, sizeof(aux));
					for(m=j; m<B; m++) {
						for(k=0; k<C; k++)
							aux[k] += aux2[m][k];

						/* use 1-D on the resulting line */
						LI max_so_far = aux[0];
						for(k=1; k<C; k++) {
							max_so_far += aux[k];
							if(aux[k] > max_so_far)
								max_so_far = aux[k];
							if(max_so_far > max)
								max = max_so_far;
						}
					}
				}
			}
		}
		/* complexity O(n^5) */
		printf("%lld\n", max);
					
		if(Ncases)
			putchar('\n');
	}
	return 0;
}
