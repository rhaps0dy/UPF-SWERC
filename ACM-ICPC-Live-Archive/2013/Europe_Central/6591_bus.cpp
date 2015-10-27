#include<iostream>
#include<algorithm>

using namespace std;

int cache[31];

int main() {
	int N;
	cin >> N;
	cache[0] = 0;
	for(int i=1; i<31; i++)
		cache[i] = cache[i-1]*2 + 1;
	while(N--) {
		int n;
		cin >> n; 
		cout << cache[n] << endl;
	}
	return 0;
}
