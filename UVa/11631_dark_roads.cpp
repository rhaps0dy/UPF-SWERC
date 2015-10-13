/**
 * Author: Daniel F.B. (Ertsiger)
 * 13/10/2015
 * Time: 0.516
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#define PB push_back
#define MP make_pair
#define X first
#define Y second
#define SZ size()

using namespace std;

typedef vector<pair<int,pair<int,int> > > V;

int N, mf[200001]; // numero de nodos N <= 200000
V v; // vector de aristas
     // (coste, (nodo1, nodo2))

int set(int n)  // conjunto conexo de n
{
    if (mf[n] == n) return n;
    else mf[n] = set(mf[n]); return mf[n];
}

int kruskal()
{
    int a, b, sum = 0;
    sort(v.begin(), v.end());
    for (int i = 0; i < N; i++)
        mf[i] = i; // inicializar conjuntos conexos

    for (int i = 0; i < (int)v.SZ; i++)
    {
        a = set(v[i].Y.X);
        b = set(v[i].Y.Y);
        
        if (a != b) // si conjuntos son diferentes
        {
            mf[b] = a; // unificar los conjuntos
            sum += v[i].X; // agregar coste de arista
        }
    }

    return sum;
}

int main()
{
    int M;
    
    while (cin >> N >> M)
    {
        if (!N && !M) break;
    
        v.clear();
    
        int n1, n2, c;
    
        int currentCost = 0;
    
        for (int i = 0; i < M; ++i)
        {
            cin >> n1 >> n2 >> c;
            currentCost += c;
            v.PB(MP(c, MP(n1, n2)));
        }
        
        int finalCost = kruskal();
        cout << currentCost - finalCost << endl;
    }

    return 0;
}

