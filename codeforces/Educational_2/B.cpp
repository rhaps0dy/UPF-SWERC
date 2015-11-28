#include<bits/stdc++.h>

using namespace std;

int a[200000];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i=0; i<n; i++)
		scanf("%d", a+i);
	sort(a, a+n);
	while(m--) {
		int b;
		scanf("%d", &b);
		int *it = upper_bound(a, a+n, b);
		printf("%d", (int)(it-a));
		if(m) putchar(' ');
	}
	putchar('\n');
	return 0;
}
