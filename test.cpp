
#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef pair<int,int> V; // tipo de costestypedef pair<V,int> P;   // par de (coste,nodo)typedef set<P> S;int N, T;vector<P> A[10001];
V dijkstra(int s, int t) {	S m;	vector<V> z(N, 1000000000);	z[s] = 0;	m.insert(MP(0, s));	while (m.SZ > 0) {		P p = *m.begin();		m.erase(m.begin());		if (p.Y == t) return p.X;		
		for (int i = 0; i < (int)A[p.Y].SZ; i++) {			P q(p.X + A[p.Y][i].X, A[p.Y][i].Y);			if (q.X < z[q.Y]) {				m.erase(MP(z[q.Y], q.Y)); // borrar anterior				m.insert(q);				z[q.Y] = q.X;				prec[q.Y] = p.Y;			}		}
	}	return -1;
}

int main() {
	while ( cin >> N >> T ) {
		
	}
}