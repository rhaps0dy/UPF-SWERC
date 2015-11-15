// Complexity: ElogV - Input: undirected graph
typedef int V;          // tipo de costes
typedef pair<V,int> P;  // par de (coste,nodo)
typedef set<P> S;       // conjunto de pares

int N;                  // numero de nodos
vector<P> A[10001];     // listas adyacencia (coste,nodo)

// int prec[201]; // predecesores (nodes from s to t)
// another way to obtain a path (above all, if there is
// more than one, consists in using BFS from the target
// and add to the queue those nodes that lead to the 
// minimum cost in the preceeding node)

V dijkstra(int s, int t) {
    S m;                          // cola de prioridad
    vector<V> z(N, 1000000000);   // distancias iniciales
    z[s] = 0;                     // distancia a s es 0
    m.insert(MP(0, s));           // insertar (0,s) en m
    while (m.SZ > 0) {
        P p = *m.begin();   // p=(coste,nodo) con menor coste
        m.erase(m.begin()); // elimina este par de m
        if (p.Y == t) return p.X; // cuando nodo es t, acaba
        // para cada nodo adjacente al nodo p.Y
        for (int i = 0; i < (int)A[p.Y].SZ; i++) {
            // q = (coste hasta nodo adjacente, nodo adjacente)
            P q(p.X + A[p.Y][i].X, A[p.Y][i].Y);
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
    N = 6;             // solucion 0-1-2-4-3-5, coste 11
    A[0].PB(MP(2, 1)); // arista (0, 1) con coste 2
    A[0].PB(MP(5, 2)); // arista (0, 2) con coste 5
    A[1].PB(MP(2, 2)); // arista (1, 2) con coste 2
    A[1].PB(MP(7, 3)); // arista (1, 3) con coste 7
    A[2].PB(MP(2, 4)); // arista (2, 4) con coste 2
    A[3].PB(MP(3, 5)); // arista (3, 5) con coste 3
    A[4].PB(MP(2, 3)); // arista (4, 3) con coste 2
    A[4].PB(MP(8, 5)); // arista (4, 5) con coste 8
    cout << dijkstra(0, 5) << endl;
}
