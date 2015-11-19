#include<iostream>
#include<cstdio>

using namespace std;

int segs[10] = {
	0b1110111, 0b0010010,
	0b1011101, 0b1011011,
	0b0111010, 0b1101011,
	0b1101111, 0b1010010,
	0b1111111, 0b1111011};

static bool
next_time(int *t) {
	t[3]++;
	if(t[3] == 10) {
		t[3] = 0;
		t[2]++;
		if(t[2] == 6) {
			t[2] = 0;
			t[1]++;
			if(t[1] == 10 || (t[0] == 2 && t[1] == 4)) {
				t[1] = 0;
				t[0]++;
				if(t[0] == 3) {
					t[0] = 0;
					return false;
				}
			}
		}
	}
	return true;
}

int times[4][50];

int main() {
	int N;
	while(cin >> N) {
		for(int i=0; i<N; i++) {
			int a, b;
			scanf("%d:%d", &a, &b);
			times[3][i] = b%10;
			times[2][i] = b/10;
			times[1][i] = a%10;
			times[0][i] = a/10;
		}
		int broken[4] = {0};
		for(int i=0; i<N; i++) {
			for(int j=0; j<4; j++)
				broken[j] |= segs[times[j][i]];
		}
		for(int j=0; j<4; j++)
			broken[j] = (~broken[j]) & 0x7f;

		int t[4], time[4] = {0};
		int nprinted=0;
		do {
			for(int i=0; i<4; i++)
				t[i] = time[i];
			bool possible = true;
			for(int i=0; i<N && possible; i++) {
				for(int j=0; j<4; j++) {
					int m = segs[t[j]] & broken[j];
					if((m | segs[times[j][i]]) != segs[t[j]])
						possible = false;
				}
				next_time(t);
			}
			if(possible) {
				if(nprinted) putchar(' ');
				nprinted++;
				printf("%d%d:%d%d", time[0], time[1], time[2], time[3]);
			}
		} while(next_time(time));
		if(!nprinted)
			puts("none");
		else
			putchar('\n');
	}
	return 0;
}
