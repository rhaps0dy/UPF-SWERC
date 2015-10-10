#include <stdio.h>
#include <string.h>

#define LEN 80

char s[LEN+1];
int memo[LEN][LEN];

#define WEIGHT(i, j) (memo[i][j] ? memo[i][j] : weight(i, j))
int weight(int i, int j) {
	int k;
	for(k=i+1; k<=j; k++)
		if(s[k] != s[i])
			goto no_len_1_cycle;
	return memo[i][j] = 1;
no_len_1_cycle:
	;
	int min = j-i+1;
	int cycle_len, max_c_len = (j-i+1)/2;
	for(cycle_len=2; cycle_len <= max_c_len; cycle_len++) {
		int cycle_last = ((j-i+1) / cycle_len) * cycle_len;
		int n;
		for(k=cycle_len; k < cycle_last; k++) {
			if(s[i+k] != s[i+k%cycle_len])
				goto next_cycle_len;
		}
		n = WEIGHT(i, i+cycle_len-1);
		if(i+cycle_last <= j)
			n += WEIGHT(i+cycle_last, j);
		if(n < min)
			min = n;
	next_cycle_len:
		;
	}
	for(k=i; k<j; k++) {
		int n = WEIGHT(i, k) + WEIGHT(k+1, j);
		if(n < min) min = n;
	}
	return memo[i][j] = min;
}


int main() {
	int i, j, k;
	while(scanf("%s", s) == 1 && strcmp(s, "*") != 0) {
		int len = strlen(s);
		memset(memo, 0, sizeof(memo));
		for(i=len-1; i>=0; i--)
			memo[i][i] = 1;
		printf("%d\n", WEIGHT(0, len-1));
#ifndef ONLINE_JUDGE
		for(i=0; i<len; i++)
			printf(" %c ", s[i]);
		putchar('\n');
		for(i=0; i<len; i++) {
			for(j=0; j<len; j++) {
				printf("%2d ", memo[i][j]);
			}
			putchar('\n');
		}
		putchar('\n');
#endif
	}
	return 0;
}
