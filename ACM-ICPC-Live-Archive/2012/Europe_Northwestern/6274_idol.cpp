#include<iostream>
#include<vector>
#include<utility>
#include<cstdio>

using namespace std;

int ind, ct;
vector<bool> I;
vector<int> D, L, S;
vector<vector<int> > V; // listas de adyacencia


void tarjan (unsigned n) {
    D[n] = L[n] = ind++;
    S.push_back(n);
    I[n] = true;
    for (unsigned i = 0; i < V[n].size(); ++i) {
        if (D[V[n][i]] < 0) {
            tarjan(V[n][i]);
            L[n] = min(L[n], L[V[n][i]]);
        }
        else if (I[V[n][i]])
            L[n] = min(L[n], D[V[n][i]]);
    }
    if (D[n] == L[n]) {
        ++ct;
        // todos los nodos eliminados de S pertenecen al mismo scc
        while (S[S.size() - 1] != n) {
            I[S.back()] = false;
            S.pop_back();
        }
        I[n] = false;
        S.pop_back();
    }
}

void scc() {
    ind = ct = 0;
    I = vector<bool>(V.size(), false);
    D = vector<int>(V.size(), -1);
    L = vector<int>(V.size());
    S.clear();
    for (unsigned n = 0; n < V.size(); ++n)
        if (D[n] < 0)
          tarjan(n);
    // ct = numero total de scc
}

#define NEGATED(u) ((u) >= N ? (u)-N : (u)+N)

int main() {
	int N, M;
	while(cin >> N >> M) {
		V = vector<vector<int> >(2*N);
		for(int i=0; i<M; i++) {
			int u, v;
			cin >> u >> v;
			if(u == 1 || v == 1)
				continue;
			if(u == -1 && v == -1)
				goto cannot;
			if(u == -1) u = v;
			if(v == -1) v = u;
			if(u<0) u = N-u;
			if(v<0) v = N-v;
			u--; v--;
			if(u != v)
				V[NEGATED(u)].push_back(v);
			V[NEGATED(v)].push_back(u);
		}
		scc();
		for(int i=0; i<N; i++) {
			if(L[i] == L[N+i])
				goto cannot;
		}
		puts("yes");
		continue;
	cannot:
		puts("no");
	}
	return 0;
}
