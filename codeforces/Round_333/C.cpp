#include<bits/stdc++.h>

using namespace std;

bool adj_mat[400][400];

vector<int> adj_list[400];
int N, R;

typedef int V;          // tipo de costes
typedef pair<V,int> P;  // par de (coste,nodo)
typedef set<P> S;       // conjunto de pares

#define MP make_pair
#define PB push_back
#define SZ size()

#define X first
#define Y second

int dijkstra(int s, int t) {
    S m;                          // cola de prioridad
    vector<V> z(N, 1000000000);   // distancias iniciales
    z[s] = 0;                     // distancia a s es 0
    m.insert(MP(0, s));           // insertar (0,s) en m
    while (m.SZ > 0) {
        P p = *m.begin();   // p=(coste,nodo) con menor coste
        m.erase(m.begin()); // elimina este par de m
        if (p.Y == t) return p.X; // cuando nodo es t, acaba
        // para cada nodo adjacente al nodo p.Y
        for (int i = 0; i < (int)adj_list[p.Y].SZ; i++) {
            // q = (coste hasta nodo adjacente, nodo adjacente)
            P q(p.X + 1, adj_list[p.Y][i]);
            // si q.X es la menor distancia hasta q.Y
            if (q.X < z[q.Y]) {
                m.erase(MP(z[q.Y], q.Y)); // borrar anterior
                m.insert(q);              // insertar q
                z[q.Y] = q.X;             // actualizar distancia
				// prec[q.Y] = p.Y;       // actualizar predecesores
            }
        }
    }
    return -1;
}

int main() {
	cin >> N >> R;
	for(int i=0; i<R; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--; v--;
		adj_mat[u][v] = adj_mat[v][u] = true;
	}
	if(R == 0 || R == N*(N-1)/2) {
		puts("-1");
	} else {
		bool direct_railway = adj_mat[0][N-1];
		if(direct_railway) {
			// we must calculate way for the bus
			for(int i=0; i<N; i++) {
				for(int j=0; j<N; j++) {
					if(!adj_mat[i][j])
						adj_list[i].push_back(j);
				}
			}
		} else {
			// calc way for the train
			for(int i=0; i<N; i++) {
				for(int j=0; j<N; j++) {
					if(adj_mat[i][j])
						adj_list[i].push_back(j);
				}
			}
		}
		printf("%d\n", dijkstra(0, N-1));
	}
	return 0;
}
