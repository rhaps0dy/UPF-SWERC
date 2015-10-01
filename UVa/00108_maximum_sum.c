#include <stdio.h>
#include <string.h>

int mat[100][100];
int aux[100];
int N;

int main() {
	int i, j, k, max, max_so_far;
	while(scanf("%d", &N) == 1) {
		for(i=0; i<N; i++)
			for(j=0; j<N; j++)
				scanf("%d", &mat[i][j]);

		max = mat[0][0];

		for(i=0; i<N; i++) {
			memset(aux, 0, sizeof(aux));
			for(k=i; k<N; k++) {
				for(j=0; j<N; j++)
					aux[j] += mat[k][j];

				max_so_far = aux[0];
				for(j=1; j<N; j++) {
					max_so_far += aux[j];
					if(aux[j] > max_so_far)
						max_so_far = aux[j];
					if(max_so_far > max)
						max = max_so_far;
				}
			}
		}
		printf("%d\n", max);
	}
	return 0;
}

