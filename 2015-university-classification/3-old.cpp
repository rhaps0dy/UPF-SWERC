#include <utility>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

#define X first
#define Y second
#define LI long long
#define MP make_pair
#define PB push_back
#define SZ size()
#define SQ(a) ((a)*(a))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef int V;          // tipo de costes
typedef pair<V,int> P;  // par de (coste,nodo)
typedef set<P> S;       // conjunto de pares

int N;                  // numero de nodos
vector<P> A[1001];     // listas adyacencia (coste,nodo)

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
      }
    }
  }
  return -1;
}

int
main()
{
    int E;
    cin >> N;
    map<string, int> cities;
    for(int i=0; i<N; i++) {
        string city;
        cin >> city;
        cities.insert(MP(city, i*2));
        // same city odd day to even day
        A[i*2].PB(MP(1, i*2+1));
        A[i*2+1].PB(MP(1, i*2));
    }
    cin >> E;
    for(int i=0; i<E; i++) {
        string na, nb;
        cin >> na >> nb;
        int ia = cities[na];
        int ib = cities[nb];
        bool even = (i % 2 == 0);

        if(even) {
            // road is open on even days
            A[ia].PB(MP(1, ib+1));
            A[ib].PB(MP(1, ia+1));
        } else {
            // road open on odd days
            A[ia+1].PB(MP(1, ib));
            A[ib+1].PB(MP(1, ia));
        }
    }

    for(int i=0; i<N*2; i++) {
        cout << i << ": ";
        for(int j = 0; j < A[i].size(); j++)
            cout << A[i][j].Y << " ";
        cout << endl;
    }

    cout << "cities " << cities["Rome"] << " " << cities["Venice"] << endl;
    int b = dijkstra(cities["Rome"], cities["Venice"]+1);
    int a = dijkstra(cities["Rome"], cities["Venice"]);
    if(a == -1) {
        cout << b << endl;
    } else if(b == -1) {
        cout << a << endl;
    } else {
        cout << MIN(a, b) << endl;
    }
    cout << dijkstra(5, 1) << endl;

    return 0;
}
