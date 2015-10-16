#include <cstdio>
#include <queue>
#include <cstdlib>

using namespace std;

int gcd(int a, int b) {
    if(a < b) return gcd(b, a);
    if(a % b == 0) return b;
    return gcd(b, a%b);
}

struct Cog {
	int x, y, r;
	int speed_num, speed_den;
	bool clockwise;
} cogs[1000];

int main() {
	int Ncases;
	scanf("%d", &Ncases);
	while(Ncases--) {
		int Nwheels;
		scanf("%d", &Nwheels);
		for(int i=0; i<Nwheels; i++) {
			scanf("%d %d %d", &cogs[i].x, &cogs[i].y, &cogs[i].r);
			cogs[i].speed_den = 0;
		}
		cogs[0].speed_num = cogs[0].speed_den = 1;
		cogs[0].clockwise = 1;

		queue<int> queue;
		queue.push(0);
		while(!queue.empty()) {
			int i = queue.front();
			queue.pop();
			for(int j=0; j<Nwheels; j++) {
				if(cogs[j].speed_den)
					continue;
				int xx = cogs[i].x - cogs[j].x;
				int yy = cogs[i].y - cogs[j].y;
				int rr = cogs[i].r + cogs[j].r;
				if(xx * xx + yy * yy == rr * rr) {
					cogs[j].speed_num = abs(cogs[i].speed_num * cogs[i].r);
					cogs[j].speed_den = abs(cogs[i].speed_den * cogs[j].r);
					int g = gcd(cogs[j].speed_num, cogs[j].speed_den);
					if(g != 0) {
						cogs[j].speed_num /= g;
						cogs[j].speed_den /= g;
					}
					cogs[j].clockwise = !cogs[i].clockwise;
					queue.push(j);
				}
			}
		}
		for(int i=0; i<Nwheels; i++) {
			if(cogs[i].speed_den == 0) {
				puts("not moving");
				continue;
			}
			if(cogs[i].speed_den == 1)
				printf("%d ", cogs[i].speed_num);
			else
				printf("%d/%d ", cogs[i].speed_num, cogs[i].speed_den);

			if(cogs[i].clockwise)
				puts("clockwise");
			else
				puts("counterclockwise");
		}
	}
	return 0;
}
	
