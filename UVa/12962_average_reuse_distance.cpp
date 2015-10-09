#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

#define SIZE ((int)'z'-'a'+1)

int main() {
	string s;
	while(cin >> s && s != "0") {
		int last_seen[SIZE];
		bool seen[SIZE];
		fill(seen, seen+SIZE, false);
		fill(last_seen, last_seen+SIZE, 0);
		int divide = 0;
		int total = 0;
		int sz = s.size();
		for(int i=0; i<sz; i++) {
			int ind = s[i] - 'a';
			int mask = 1 << ind;
			if(seen[ind]) {
				total += __builtin_popcount(last_seen[ind]);
				divide++;
			} else {
				seen[ind] = true;
			}
			for(int j=0; j<SIZE; j++)
				last_seen[j] |= mask;
			last_seen[ind] = 0;
		}
		if(divide == 0) {
			puts("NaN");
		} else {
			printf("%.4lf\n", ((double)total)/((double)divide));
		}
	}
	return 0;
}
