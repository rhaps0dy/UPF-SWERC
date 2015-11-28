#include<bits/stdc++.h>

using namespace std;

typedef long long LI;

int main() {
	LI a, b;
	LI ba, bb;
	int na, nb;
	cin >> na;
	cin >> ba;
	a=0;
	while(na--) {
		LI n;
		cin >> n;
		a *= ba;
		a += n;
	}
	cin >> nb;
	cin >> bb;
	b=0;
	while(nb--) {
		LI n;
		cin >> n;
		b *= bb;
		b += n;
	}
	if(a == b) {
		puts("=");
	} else if(a > b) {
		puts(">");
	} else {
		puts("<");
	}
	return 0;
}
