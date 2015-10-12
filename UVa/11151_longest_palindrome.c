#include <stdio.h>
#include <string.h>

char s[1001];
int memo[1000][1000];

#define LONGEST_PAL(i, j) (j < i ? 0 : (memo[i][j] != 0 ? memo[i][j] : longest_pal(i, j)))
int longest_pal(int i, int j) {
	if(s[i] == s[j])
		return memo[i][j] = 2 + LONGEST_PAL(i+1, j-1);
	int a = LONGEST_PAL(i+1, j), b = LONGEST_PAL(i, j-1);
	return memo[i][j] = (a > b ? a : b);
}

int main() {
	int Ncases, i, j;
	scanf("%d", &Ncases);
	gets(s);
	while(Ncases--) {
		gets(s);
		int len = strlen(s);
		memset(memo, 0, sizeof(memo));
		for(i=0; i<len; i++)
			memo[i][i] = 1;
		printf("%d\n", LONGEST_PAL(0, len-1));
	}
	return 0;
}
