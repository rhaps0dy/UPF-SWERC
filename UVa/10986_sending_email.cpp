/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 01/10/2015
 * Time: 0.246
 */
#include <iostream>
#include <set>
#include <vector>
#include <utility>

#define X first
#define Y second
#define SZ size()
#define MP make_pair
#define PB push_back

using namespace std;

typedef int V;          // tipo de costes
typedef pair<V,int> P;  // par de (coste,nodo)
typedef set<P> S;       // conjunto de pares

int N;                  // numero de nodos
vector<P> A[20001];     // listas adyacencia (coste,nodo)

V dijkstra(int s, int t)
{
	S m;                          // cola de prioridad
	vector<V> z(N, 1000000000);   // distancias iniciales
	z[s] = 0;                     // distancia a s es 0
	m.insert(MP(0, s));           // insertar (0,s) en m
	
	while (m.SZ > 0)
	{
		P p = *m.begin();   // p=(coste,nodo) con menor coste
		m.erase(m.begin()); // elimina este par de m
		if (p.Y == t) return p.X; // cuando nodo es t, acaba
		
		// para cada nodo adjacente al nodo p.Y
		for (int i = 0; i < (int)A[p.Y].SZ; i++)
		{
			// q = (coste hasta nodo adjacente, nodo adjacente)
			P q(p.X + A[p.Y][i].X, A[p.Y][i].Y);
			
			// si q.X es la menor distancia hasta q.Y
			if (q.X < z[q.Y])
			{
				m.erase(MP(z[q.Y], q.Y)); // borrar anterior
				m.insert(q);              // insertar q
				z[q.Y] = q.X;             // actualizar distancia
			}
		}
	}
	
	return -1;
}

int main()
{
	int T = 0;
	cin >> T;
	
	for (int c = 1; c <= T; ++c)
	{
		int m, s, t;
		cin >> N >> m >> s >> t;
				
		for (int i = 0; i < N; ++i) A[i].clear();
		
		int n1, n2, w;
		
		for (int i = 0; i < m; ++i)
		{
			cin >> n1 >> n2 >> w;
			A[n1].PB(MP(w, n2));
			A[n2].PB(MP(w, n1));
		}
		
		int cost = dijkstra(s, t);
		
		cout << "Case #" << c << ": ";
		
		if (cost >= 0)
		{
			cout << cost << "\n";
		}
		else
		{
			cout << "unreachable\n";
		}
	}

	return 0;
}

