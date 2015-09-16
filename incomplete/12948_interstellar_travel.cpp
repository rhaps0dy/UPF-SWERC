#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <climits>
#include <queue>
#include <set>

#define X first
#define Y second
#define LI long long
#define MP make_pair
#define PB push_back
#define SZ size()
#define SQ(a) ((a)*(a))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define FOR(i,x,y) for(int i=(int)x; i<(int)y; i++)
#define RFOR(i,x,y) for(int i=(int)x; i>(int)y; i--)
#define SORT(a) sort(a.begin(), a.end())
#define RSORT(a) sort(a.rbegin(), a.rend())
#define IN(a,pos,c) insert(a.begin()+pos,1,c)
#define DEL(a,pos,cant) erase(a.begin()+pos,cant)

using namespace std;

typedef struct Node
{
	int _p; // planet
	int _d; // depth
	int _t; // time
	int _c; // cost (money)
	
	Node(int p, int d, int c, int t): _p(p), _d(d), _t(t), _c(c)
	{
	}

	int cost() const
	{
		return _t + _c;
	}
} Node;

struct node_cmp
{
	bool operator() (const Node& n1, const Node& n2) const
	{
		if (n1._c == n2._c)
		{
			return n1._p < n2._p;			
		}
		
		return n1._c < n2._c;
	}
};

typedef int V;          // tipo de costes
typedef pair< pair<int, int>, int> P; // par de (coste,nodo)
typedef set<Node, node_cmp> S;       // conjunto de pares

int N;                  // numero de nodos
vector<P> A[10001];     // listas adyacencia (coste,nodo)

int PL = 0; // num planets
int F = 0; // num flights
int Q = 0; // num queries

pair<int, int> dijkstra(int s, int t, int d)
{
	S m;                          // cola de prioridad
	vector<V> z(N, 1000000000);   // distancias iniciales
	z[s] = 0;                     // distancia a s es 0
	
	Node node(s, -1, 0, 0);
	m.insert(node);           // insertar (0,s) en m

	while (m.SZ > 0)
	{
		Node p = *m.begin();   // p=(coste,nodo) con menor coste
		m.erase(m.begin()); // elimina este par de m
		
		if (p._p == t)
		{
			return make_pair(p._c, p._t); // cuando nodo es t, acaba
		}
		
		if (p._d > d)
		{
			continue;
		}
		
		// para cada nodo adjacente al nodo p.Y
		for (int i = 0; i < (int)A[p._p].SZ; i++)
		{
			// q = (coste hasta nodo adjacente, nodo adjacente)
			Node q(A[p._p][i].Y, p._d + 1, p._c + A[p._p][i].X.X, p._t + A[p._p][i].X.Y);
			
			// si q.X es la menor distancia hasta q.Y
			if (q._c <= z[q._p])
			{
				Node toerase(q._p, 0, z[q._p], 0); // same cost 0 + z[q._p] = z[q._p]				
				m.erase(toerase); 				   // borrar anterior
				m.insert(q);              		   // insertar q
				z[q._p] = q._c;                // actualizar distancia
			}
		}
	}
	
	return make_pair(-1, -1);
}

int main()
{
	bool firstcase = true;
	
	while (cin >> PL >> F >> Q)
	{
		if (!firstcase)
		{
			cout << ".\n";
		}
		
		firstcase = false;
		
		map<string, int> planets;
		string planet = "";
	
		for (int i = 0; i < PL; ++i)
		{
			cin >> planet;
			planets[planet] = i;
			A[i].clear();
		}
		
		string p1 = "";
		string p2 = "";
		int c = 0;
		int t = 0;
		
		for (int i = 0; i < F; ++i)
		{
			cin >> p1 >> p2 >> c >> t;
			A[planets[p1]].push_back(make_pair(make_pair(c, t), planets[p2]));
		}
		
		string si = "";
		cin >> si;
		
		string sf = "";
		int n = 0;
		
		N = PL;
		
		for (int i = 0; i < Q; ++i)
		{
			cin >> sf >> n;
			
			pair<int, int> accost = dijkstra(planets[si], planets[sf], n);
			
			if (accost.X < 0)
			{
				cout << "* *\n";
			}
			else
			{
				cout << accost.X << " " << accost.Y << endl;
			}
		}
	}

	return 0;
}

