#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#define X first
#define Y second
#define LI long long
#define MP make_pair
#define PB push_back
#define SZ size()
#define SQ(a) ((a)*(a))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define FOR(i,x,y) for(int i=(int)x; i<(int)y; i++)
#define RFOR(i,x,y) for(int i=(int)x; i>(int)y; i--)
#define SORT(a) sort(a.begin(), a.end())
#define RSORT(a) sort(a.rbegin(), a.rend())
#define IN(a,pos,c) insert(a.begin()+pos,1,c)
#define DEL(a,pos,cant) erase(a.begin()+pos,cant)

using namespace std;

typedef vector<pair<long, pair<int, int> > > V;

int N = 0; // number of nodes/places

int mf[3001]; // numero de nodos N <= 2000
V v; // vector de aristas

vector< pair<long, int> > K[3001]; // kruskal tree
bool vis[3001];

int set(int n) { // conjunto conexo de n
	if (mf[n] == n) return n;
	else mf[n] = set(mf[n]); return mf[n];
}

int kruskal() {
	int a, b, sum = 0;
	sort(v.begin(), v.end());
	for (int i = 0; i <= N; i++)
		mf[i] = i; // inicializar conjuntos conexos

	for (int i = 0; i < (int)v.SZ; i++) {
		a = set(v[i].Y.X), b = set(v[i].Y.Y);
		if (a != b) { // si conjuntos son diferentes
			mf[b] = a;  // unificar los conjuntos
			sum += v[i].X; // agregar coste de arista
			K[v[i].Y.X].PB(MP(v[i].X, v[i].Y.Y));
			K[v[i].Y.Y].PB(MP(v[i].X, v[i].Y.X));
		}
	}
	return sum;
}


bool func(int nodeid, int nodesearch, long& maxDist)
{
	vis[nodeid] = true;

	if (nodeid == nodesearch) return true;

	vector< pair<long, int> >& neigh = K[nodeid];

	for (int i = 0; i < neigh.size(); ++i)
	{
		if (!vis[neigh[i].Y] && func(neigh[i].Y, nodesearch, maxDist))
		{
			maxDist = max(maxDist, neigh[i].X);
			return true;
		}
	}

	return false;
}


int main()
{
	long T = 0; // test cases

	cin >> T;

	for (long i = 1; i <= T; ++i)
	{
		cout << "Case " << i << endl;

		v.clear();

		long R; // number of roads
		cin >> N >> R;

		for (int j = 1; j <= N; ++j)
		{
			K[j].clear();
			vis[j] = false;
		}
		
		int a, b;
		long l;

		for (long j = 0; j < R; ++j)
		{
			cin >> a >> b >> l;
			v.PB(MP(l, MP(a, b)));
		}

		kruskal();

		/*
		for (int j = 1; j <= N; ++j)
		{
			for (int k = 0; k < K[j].size(); ++k)
			{
				cout << j << ", " << K[j][k].Y << " --> " << K[j][k].X << endl;
			}
		}
		*/

		int Q; // number of queries
		cin >> Q;

		for (int j = 0; j < Q; ++j)
		{
			cin >> a >> b;

			long maxDist = -1;
			func(a, b, maxDist);

			cout << maxDist << endl;

			for (int k = 1; k <= N; ++k) vis[k] = false;
		}

		cout << endl;
	}

	return 0;
}
