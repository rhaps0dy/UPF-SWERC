// Complexity |V| + |E|
int index, ct;
vector<bool> I;
// L indica el indice del conjunto fuertemente conexo al que pertenece cada nodo
vector<int> D, L, S;
vector<vector<int> > V; // listas de adyacencia (grafo dirigido)

void tarjan (unsigned n) {
    D[n] = L[n] = index++;
    S.push_back(n);
    I[n] = true;
    for (unsigned i = 0; i < V[n].size(); ++i) {
        if (D[V[n][i]] < 0) {
            tarjan(V[n][i]);
            L[n] = MIN(L[n], L[V[n][i]]);
        }
        else if (I[V[n][i]])
            L[n] = MIN(L[n], D[V[n][i]]);
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
    index = ct = 0;
    I = vector<bool>(V.size(), false);
    D = vector<int>(V.size(), -1);
    L = vector<int>(V.size());
    S.clear();
    for (unsigned n = 0; n < V.size(); ++n)
        if (D[n] < 0)
          tarjan(n);
    // ct = numero total de scc
}
