#include <cstdio>
#include <map>
#include <climits>

using namespace std;

#define MAX 46343
long long power[MAX];

int main() {
	map<int, int> results;
	int n, p;
	long long i;

	for(i=0; i<MAX; i++)
		power[i] = i;

	for(p=2; p<=31; p++) {
		for(i=2; (power[i] *= i) <= INT_MAX; i++) {
			results[(int)power[i]] = p;
			if(p%2 == 1)
				results[-(int)power[i]] = p;
		}
	}
	results[INT_MIN] = 31;

	while(scanf("%d", &n) == 1 && n != 0) {
		if(results.find(n) == results.end())
			puts("1");
		else
			printf("%d\n", results[n]);
	}
	return 0;
}
