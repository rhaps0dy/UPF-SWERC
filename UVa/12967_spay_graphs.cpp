#include <iostream>
#include <cstdio>
using namespace std;

int cam[30][30];

int main() {
	int Ncases;
	cin >> Ncases;
	while(Ncases--) {
		int sz;
		cin >> sz;
if(sz == 1) { cout << 1 << endl; continue; }
		for(int i=0; i<sz-1; i++) {
			cam[0][i] = i+1;
			cam[i][0] = 1;
		}
		int i, j = 1;
		for(i=1; i < sz-1; i++) {
			for(j=1; j+1< sz-1; j++)
				cam[i][j] = cam[i][j-1] + cam[i-1][j];
		}
		int sum = 0;
		for(i=0; i<sz-1; i++) {
			sum += cam[sz-2-i][i];
		}
		cout << sum*4 << endl;
	}
	return 0;
}
