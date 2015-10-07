#include <stdio.h>

#define MAX 2000

int inc[MAX], dec[MAX];
int seq[MAX], N;

int main() {
	int Ncases, i, j;
	scanf("%d", &Ncases);
	while(Ncases--) {
		scanf("%d", &N);
		for(i=0; i<N; i++)
			scanf("%d", &seq[i]);

		for(i=N-1; i>=0; i--) {
			inc[i] = dec[i] = 1;
			for(j=i+1; j<N; j++) {
				if(seq[i] < seq[j]) {
					int v = inc[j] + 1;
					if(v > inc[i])
						inc[i] = v;
				} else { /* no two are equal */
					int v = dec[j] + 1;
					if(v > dec[i])
						dec[i] = v;
				}
			}
		}
		int max = 0;
		for(i=0; i<N; i++) {
			int v = inc[i] + dec[i] - 1;
			if(v > max)
				max = v;
		}
		
		printf("%d\n", max);
	}
	return 0;
}
