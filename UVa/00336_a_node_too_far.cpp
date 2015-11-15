#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define X first
#define Y second
#define LI long long
#define MP make_pair
#define PB push_back
#define SZ size()
#define SQ(a) ((a)*(a))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

using namespace std;

int N;                  // numero de nodos
vector<int> A[31];   // listas de adyacencia

int BFS(int s, int t) { // distancia entre s y t
  if (s == t) return 0;
  int l[31], k = 0;  // inicializar cola
  vector<int> v(N, -1); // inicializar distancias
  l[k++] = s;           // agregar s a la cola
  v[s] = 0;             // distancia hasta s es 0
  for (int i = 0; i < k; i++)
    // para todos los nodos adyacentes de l[i]
    for (int j = 0; j < (int)A[l[i]].SZ; j++)
      // si el vecino no se ha visitado
      if (v[A[l[i]][j]] < 0) {
        // actualizar su distancia
	v[A[l[i]][j]] = v[l[i]] + 1;
        // si encontramos t, devolver resultado
	if (A[l[i]][j] == t) return v[t];
        // agregar a la cola
	l[k++] = A[l[i]][j];
      }
  return -1;
}

int main()
{
    int C = 0;
    int casen = 1;

    while (cin >> C)
    {
        if (!C) break;

        int indexNode = 0;
        map<int, int> nodesToIndex;
        map<int, int> indexToNodes;

        for (int i = 0; i < 31; ++i)
        {
            A[i].clear();
        }

        int f, s;

        for (int i = 0; i < C; ++i)
        {
            cin >> f >> s;

            if (nodesToIndex.find(f) == nodesToIndex.end())
            {
                indexToNodes[indexNode] = f;
                nodesToIndex[f] = indexNode++;
            }

            if (nodesToIndex.find(s) == nodesToIndex.end())
            {
                indexToNodes[indexNode] = s;
                nodesToIndex[s] = indexNode++;
            }

            A[nodesToIndex[f]].push_back(nodesToIndex[s]);
            A[nodesToIndex[s]].push_back(nodesToIndex[f]);
        }

        N = nodesToIndex.size();

        int node, ttl;

        while (cin >> node >> ttl)
        {
            if (!node && !ttl) break;

            int indexNode = nodesToIndex[node];

            int out = 0;
            int d = 0;

            for (int i = 0; i < N; ++i)
            {
                if (i != indexNode)
                {
                    d = BFS(indexNode, i);

                    if (d > ttl || d == -1) ++out;
                }
            }

            cout << "Case " << casen++ << ": " << out << " nodes not reachable from node " << node << " with TTL = " << ttl << "." << endl;
        }
    }

    return 0;
}

