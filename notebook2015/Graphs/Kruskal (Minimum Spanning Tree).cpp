// Complexity: ElogV - Input: undirected graph
typedef vector<pair<int,pair<int,int> > > V;

int N, mf[2000]; // numero de nodos N <= 2000
V v;             // vector de aristas
                 // (coste, (nodo1, nodo2))

// vector< pair<long, int> > K[3001]; // kruskal tree

int set(int n) { // conjunto conexo de n
    if (mf[n] == n) return n;
    else mf[n] = set(mf[n]); return mf[n];
}

int kruskal() {
    int a, b, sum = 0;
    sort(v.begin(), v.end());
    for (int i = 0; i < N; i++)
        mf[i] = i; // inicializar conjuntos conexos
    for (int i = 0; i < (int)v.SZ; i++) {
        a = set(v[i].Y.X), b = set(v[i].Y.Y);
        if (a != b) { // si conjuntos son diferentes
            mf[b] = a;  // unificar los conjuntos
            sum += v[i].X; // agregar coste de arista
			// K[v[i].Y.X].PB(MP(v[i].X, v[i].Y.Y));
			// K[v[i].Y.Y].PB(MP(v[i].X, v[i].Y.X));
        }
    }
    return sum;
}

int main() {
    N = 5; // solucion 13 (0,3),(1,2),(2,3),(3,4)
    v.PB(MP(4,MP(0,1))); // arista (0,1) coste 4
    v.PB(MP(4,MP(0,2))); // arista (0,2) coste 4
    v.PB(MP(3,MP(0,3))); // arista (0,3) coste 3
    v.PB(MP(6,MP(0,4))); // arista (0,4) coste 6
    v.PB(MP(3,MP(1,2))); // arista (1,2) coste 3
    v.PB(MP(7,MP(1,4))); // arista (1,4) coste 7
    v.PB(MP(2,MP(2,3))); // arista (2,3) coste 2
    v.PB(MP(5,MP(3,4))); // arista (3,4) coste 5
    cout << kruskal() << endl;
}

