#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Person {
	int t, s, f, e, dir;
} pp[1000];

int greetn[1000];

int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		for(int i=0; i<n; i++) {
			scanf("%d %d %d", &pp[i].t, &pp[i].s, &pp[i].f);
			pp[i].dir = (pp[i].f < pp[i].s ? -1 : 1);
			pp[i].e = pp[i].t + (pp[i].f - pp[i].s) * pp[i].dir;
		}
		memset(greetn, 0, sizeof(greetn));
#define GREET do { greetn[i]++; greetn[j]++; } while(0)
		for(int i=0; i<n; i++) {
			for(int j=i+1; j<n; j++) {
				Person a, b;
				a = pp[i];
				b = pp[j];
				if(a.t <= b.t) {
					a.s = a.s + a.dir*(b.t - a.t);
					a.t = b.t;
					if(a.e < a.t)
						continue;
				} else {
					b.s = b.s + b.dir*(a.t - b.t);
					b.t = a.t;
					if(b.e < b.t)
						continue;
				}
				if(a.s == b.s) {
					GREET;
					continue;
				} else if(a.s > b.s) {
					swap(a, b);
				}
/*				printf("empezar: %d %d\n", a.s, b.s);
				printf("finalizar: %d %d\n", a.f, b.f); */

				if(a.dir == 1 && b.dir == -1) {
					if(a.e < b.e) {
						b.f = b.s + b.dir*(a.e - b.t);
					} else if(b.e < a.e) {
						a.f = a.s + a.dir*(b.e - a.t);
					}
					if(a.f >= b.f)
						GREET;
				}
			}
		}
		printf("%d", greetn[0]);
		for(int i=1; i<n; i++)
			printf(" %d", greetn[i]);
		putchar('\n');
	}
	return 0;
}
