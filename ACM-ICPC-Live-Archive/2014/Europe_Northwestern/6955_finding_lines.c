#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct {int x, y;} points[100000];

int main() {
	int N, P;
	while(scanf("%d %d", &N, &P) == 2) {
		int i;
		for(i=0; i<N; i++)
			scanf("%d %d", &points[i].x, &points[i].y);
		int n_req = N*P;
		if(n_req%100 == 0)
			n_req /= 100;
		else
			n_req = n_req / 100 + 1;
		if(n_req <= 2 || N <= 2)
			goto possible;
		n_req -= 2;

		for(i=0; i<250; i++) {
			int n = 0;
			int a = rand()%N, b = a;
			while(b==a)
				b = rand()%N;
			int c;
			int vx = points[b].x - points[a].x, vy = points[b].y - points[a].y;
			for(c=0; c<N; c++) {
				if(c==a || c==b) continue;
				int wx = points[c].x - points[a].x, wy = points[c].y - points[a].y;
				if((vx==0 && wx==0) || (vy==0 && wy==0)) {
					if((++n) >= n_req)
						goto possible;
				} else if(wx*vy == wy*vx) {
					if((++n) >= n_req)
						goto possible;
				}
			}
		}
		puts("impossible");
		continue;
possible:
		puts("possible");
	}
	return 0;
}
