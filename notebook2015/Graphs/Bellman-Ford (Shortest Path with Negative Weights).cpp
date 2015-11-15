// Complexity: V * E
typedef pair<pair<int,int>,int> P; // par de nodos + coste
int N;                             // numero de nodos
vector<P> v;                       // representacion aristas

int bellmanford(int a, int b) {
    vector<int> d(N, 1000000000);
    d[a] = 0;
    for (int i = 1; i < N; i++)
        for (int j = 0; j < (int)v.SZ; j++)
            if (d[v[j].X.X] < 1000000000 && d[v[j].X.X] + v[j].Y < d[v[j].X.Y])
                d[v[j].X.Y] = d[v[j].X.X] + v[j].Y;
        for (int j = 0; j < (int)v.SZ; j++)
            if (d[v[j].X.X] < 1000000000 && d[v[j].X.X] + v[j].Y < d[v[j].X.Y])
                return -1000000000; // existe ciclo negativo
    return d[b];
}
