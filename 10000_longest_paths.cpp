#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

#define PB push_back
#define SZ size()
#define X first
#define Y second
#define MP make_pair

int N;
vector<int> adjlists[100];

pair<int, int>
get_longest_path(int from)
{
	if(adjlists[from].SZ == 0)
		return MP(0, from);

	pair<int, int> rec = MP(-1, 0);
	for(int i=0; i<(int)adjlists[from].SZ; i++) {
		pair<int, int> res = get_longest_path(adjlists[from][i]);
		if(res.X > rec.X) rec = res;
	}
	rec.X++;
	return rec;
}

int main()
{
	int S, p, q;
	pair<int, int> res;

	cin >> N;
	for(int j=1;;j++) {
		for(int i=0; i<N; i++)
			adjlists[i].clear();
		cin >> S;
		S-=1;
		for(;;) {
			cin >> p >> q;
			if(p==0 && q==0) break;
			adjlists[p-1].PB(q-1);
		}
		res = get_longest_path(S);
		printf("Case %d: The longest path from %d has length %d, finishing at %d.\n",
				j, S+1, res.X, res.Y+1);
		cin >> N;
		if(N==0) return 0;
		putchar('\n');
	}
	return 0;
}
