#include <iostream>
#include <cstdio>

using namespace std;

#define PB push_back
#define SZ size()
#define X first
#define Y second
#define MP make_pair
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int N, S;
int adjmat[100][100];

int main()
{
	int p, q;

	cin >> N;
	for(int ncase=1;;ncase++) {
		cin >> S;
		S-=1;
		for(int j=0; j<N; j++)
			for(int i=0; i<N; i++)
				adjmat[j][i] = 1000000000;
		for(;;) {
			cin >> p >> q;
			if(p==0 && q==0) break;
			adjmat[p-1][q-1] = -1;
		}
		for(int k=0; k<N; k++)
			for(int j=0; j<N; j++)
				for(int i=0; i<N; i++)
					adjmat[i][j] = MIN(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
		int rec = 0;
		int res;
		for(int i=0; i<N; i++) {
			if(adjmat[S][i] < rec) {
				rec = adjmat[S][i];
				res = i;
			}
		}
		printf("Case %d: The longest path from %d has length %d, finishing at %d.\n",
				ncase, S+1, -rec, res+1);

		cin >> N;
		if(N==0) return 0;
		putchar('\n');
	}
	return 0;
}
