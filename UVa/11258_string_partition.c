#include <stdio.h>
#include <limits.h>

typedef long long LI;

LI s[200];
LI memo[200][200];

const LI MAX_N = (LI) INT_MAX;

#define MAX_SUM(i, j) (memo[i][j] != -1 ? memo[i][j] : max_sum(i, j))
LI max_sum(int i, int j) {
	int k;
	LI max = 0;
	for(k=i; k<=j && max <= MAX_N; k++) {
		max *= 10;
		max += s[k];
	}
	if(max > MAX_N)
		max /= 10;
	for(k=i; k<j; k++) {
		LI m = MAX_SUM(i, k) + MAX_SUM(k+1, j);
		if(m > max)
			max = m;
	}
	return memo[i][j] = max;
}

int main() {
	int Ncases, i, j;
	scanf("%d", &Ncases);
	while(getchar() != '\n');
	while(Ncases--) {
		int len = 0;
		while((s[len] = (int)getchar()) != ((int)'\n'))
			s[len++] -= '0';
		for(i=0; i<len; i++) {
			memo[i][i] = s[i];
			for(j=i+1; j<len; j++)
				memo[i][j] = -1;
		}
		printf("%lld\n", max_sum(0, len-1));
	}
	return 0;
}
