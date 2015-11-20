#define U unsigned int
typedef vector<short int> V;

vector<vector<U> > graf; // vertices/aristas del grafo
U numv, kmax; // # conjuntos/tamano grupo independiente

int evalua(V &vec) {
    for (int n = 0; n < vec.size(); n++)
        if (vec[n] == 1) return n;
    return -1;
}

void Bron_i_Kerbosch() {
    vector<U> v;
    U i, j, aux, k = 0, bandera = 2;
    vector<V> I, Ve, Va;
    I.PB(V()); Ve.PB(V()); Va.PB(V());
    for (i = 0; i < numv; i++) {
        I[0].PB(0);  // conjunto vacio
        Ve[0].PB(0); // conjunto vacio
        Va[0].PB(1); // contiene todos
    } 
    while(true) {
        switch(bandera) {
        case 2: // paso 2
            v.PB(evalua(Va[k]));
            I.PB(V(I[k].begin(), I[k].end()));
            Va.PB(V(Va[k].begin(), Va[k].end()));
            Ve.PB(V(Ve[k].begin(), Ve[k].end()));
            aux = graf[v[k]].size();
            I[k+1][v[k]] = 1; Va[k+1][v[k]] = 0;      
            for (i = 0; i < aux; i++) {
                j = graf[v[k]][i]; Ve[k+1][j] = Va[k+1][j] = 0;
            }
            k = k + 1; bandera = 3; 
            break;
        /**********************************************/          
        case 3: // paso 3
            for (i = 0, bandera = 4; i < numv; i++) {
                if (Ve[k][i] == 1) {
                    aux = graf[i].size();
                    for (j = 0; j < aux; j++)
                        if (Va[k][graf[i][j]] == 1) 
                            break;
                    if (j == aux) { i = numv; bandera = 5; }
                }
            } 
            break;
        /**********************************************/
        case 4: // paso 4
            if (evalua(Ve[k]) == -1 && evalua(Va[k]) == -1) {
                for (int n = 0; n < numv; n++)
                    if (I[k][n] == 1) cout<< n << " ";
                cout << endl;
                if (k > kmax) kmax = k;
                bandera = 5;
            }
            else bandera = 2; // ir a paso 2
        break;
        /**********************************************/
        case 5: // paso 5
            k = k - 1; v.pop_back(); I[k].clear();
            I[k].assign(I[k+1].begin(), I[k+1].end());
            I[k][v[k]] = 0; I.pop_back(); Ve.pop_back();
            Va.pop_back(); Ve[k][v[k]] = 1; Va[k][v[k]] = 0;
            if (k == 0) {
                if (evalua(Va[0]) == -1) return;
                bandera = 2; // ir a paso 2
            }
            else bandera = 3; // ir a paso 3
        break;
        }
    }     
}

int main() {
    U idx, i; stringstream ss; string linea;
    while (cin >> numv) {
        getline(cin, linea);
        for (i = 0; i < numv; i++) { // Lectura del grafo
            // vertices adjacentes al i-esimo vertice
            vector<U> bb; graf.PB(bb);
            getline(cin, linea);
            ss << linea;
            while (ss >> idx) graf[i].PB(idx);
            ss.clear();
        }
        // Llamada al algoritmo
        kmax = 0;
        cout << "Conjuntos independientes: "<< endl;
        if (numv > 0)
            Bron_i_Kerbosch();
        cout << "kmax: " << kmax << endl;
        // Limpieza variables
        for (i = 0; i < numv; i++) graf[i].clear();
        graf.clear();
    }
}
