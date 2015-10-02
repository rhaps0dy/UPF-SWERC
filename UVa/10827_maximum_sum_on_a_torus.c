#include <stdio.h>
#include <string.h>

#define MAX 75

int mat[MAX][MAX];
int aux[MAX];
int aux2[MAX];
int N;

static int
kadane(int *arr) {
	int max, max_here, j;
	max = max_here = arr[0];
	for(j=1; j<N; j++) {
		max_here += arr[j];
		if(arr[j] > max_here)
			max_here = arr[j];
		if(max_here > max)
			max = max_here;
	}
	return max;
}

static int
step(int k) {
	int j, max_kadane, sum;

	sum = 0;
	for(j=0; j<N; j++) {
		aux[j] += mat[k][j];
		sum += aux[j];
		aux2[j] = -aux[j];
	}

	max_kadane = kadane(aux);

	int k2 = kadane(aux2);
	sum += k2;
	if(sum > max_kadane)
		return sum;
	return max_kadane;
}

int main() {
	int i, j, k, max;
	int Ncases;
	scanf("%d", &Ncases);
	
	while(Ncases--) {
		scanf("%d", &N);
		for(i=0; i<N; i++)
			for(j=0; j<N; j++)
				scanf("%d", &mat[i][j]);

		max = mat[0][0];
		
		if(N > 1) {
			memset(aux, 0, sizeof(aux));
			for(k=0; k<N; k++) {
				int m = step(k);
				if(m > max)
					max = m;
			}

			for(i=1; i<N; i++) {
				memset(aux, 0, sizeof(aux));
				for(k=i; k != i-1; k = (k+1)%N) {
					int m = step(k);
					if(m > max)
						max = m;
				}
			}
		}
		printf("%d\n", max);
	}
	return 0;
}

