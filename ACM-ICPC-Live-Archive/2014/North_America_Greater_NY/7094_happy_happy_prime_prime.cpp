#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int is_happy(int n, int depth) {
	static char number[100];

	if(!depth)
		return 0;

	int i;
	sprintf(number, "%d", n);
	int sum = 0;
	for(i=0; number[i]; i++) {
		int nn = number[i] - '0';
		sum += nn * nn;
	}
	if(sum == 1)
		return 1;
	return is_happy(sum, depth-1);
}

#define MAX 10010

int sieve[MAX];

int main() {
	int N, n_case, i, j, k;

	fill(sieve, sieve+MAX, true);
	for(i=2; i*i<=MAX; i++) {
		for(j=2; (k=j*i) < MAX; j++)
			sieve[k] = false;
	}
	
	scanf("%d", &N);
	for(n_case=1; n_case<=N; n_case++) {
		int n;
		scanf("%*d %d", &n);

		printf("%d %d ", n_case, n);
		if(n >= 7) {
			if(sieve[n] && is_happy(n, 30))
				puts("YES");
			else
				puts("NO");
		} else {
			puts("NO");
		}
	}
	return 0;
}
