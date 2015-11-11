/**
 * Daniel F.B. (Ertsiger)
 * 11/11/2015
 * Time: 0.079
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

#define X first
#define Y second
#define MP make_pair
#define PB push_back
#define SZ size()

using namespace std;

typedef vector<pair<int,pair<int,int> > > V;

int mf[2001]; 

int set(int n) // conjunto conexo de n
{ 
  if (mf[n] == n) return n;
  else mf[n] = set(mf[n]); return mf[n];
}

int kruskal(int N, V& v)
{
    int a, b, sum = 0;
    sort(v.begin(), v.end());
    for (int i = 0; i < N; i++)
        mf[i] = i; // inicializar conjuntos conexos

    for (int i = 0; i < (int)v.SZ; i++)
    {
        a = set(v[i].Y.X), b = set(v[i].Y.Y);
        if (a != b) // si conjuntos son diferentes
        { 
            mf[b] = a;  // unificar los conjuntos
            sum += v[i].X; // agregar coste de arista
        }
    }
    
    return sum;
}

int main()
{
    int T = 0;
    cin >> T;

    int N; // num cities
    int M; // num links
    
    while (T--)
    {
        cin >> N >> M;
        
        V v; // vector de aristas (coste, (nodo1, nodo2))

        string s1, s2;
        int s1i, s2i, cost;
        
        map<string, int> cities;
        int cityId = 0;
        
        for (int i = 0; i < M; ++i)
        {
            cin >> s1 >> s2 >> cost;
            
            if (cities.find(s1) == cities.end())
            {
                cities[s1] = cityId++;
            }
            
            if (cities.find(s2) == cities.end())
            {
                cities[s2] = cityId++;
            }
            
            s1i = cities[s1];
            s2i = cities[s2];
            
            v.PB(MP(cost, MP(s1i, s2i)));
        }
        
        cout << kruskal(N, v) << "\n";
        
        if (T >= 1)
        {
            cout << "\n";
        }
    }
    
    return 0;
}

