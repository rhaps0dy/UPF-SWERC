/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 20/09/2015
 * Time: 2.142
 */
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <utility>
#include <cassert>

#define X first
#define Y second
#define LI long long
#define MP make_pair
#define PB push_back
#define SZ size()

using namespace std;

typedef int V;          // cost type
typedef pair<V, int> P; // pair (cost,node)
typedef set<P> S;       // set of pairs

int N; // number of nodes
map<int, pair<V, int> > A[250001];  // adjacency list {node, {cost, paths}}

V z[10001]; // array of minimum cost from the root (0) to any node in the graph
bool visited[10001]; // array of already visited nodes

// Dijkstra algorithm to fill the array 'z'
V dijkstra(int s, int t)
{
	S m;                          // priority queue
	z[s] = 0;                     // distance from s is 0
	m.insert(MP(0, s));           // insert (0,s) in m

	while (m.SZ > 0)
	{
		P p = *m.begin();   // p=(cost,node) with least cost
		m.erase(m.begin()); // erase this pair from m

		if (p.Y == t)
		{
			return p.X; // when the node is t, finish
		}

		// for each node adjacent to p.Y
		map<int, pair<V, int> >::iterator it = A[p.Y].begin();
		
		for (; it != A[p.Y].end(); ++it)
		{
			// q = (cost to adjacent node, adjacent node)
			P q(p.X + it->second.first, it->first);

			// if q.X is the lowest distance to q.Y
			if (q.X < z[q.Y])
			{
				m.erase(MP(z[q.Y], q.Y)); // erase the last one
				m.insert(q);              // insert q
				z[q.Y] = q.X;             // update distance
			}
		}
	}

	return -1;
}

// BFS (Breadth-First Search) is used to compute the whole length of the paths
// to fill with flowers. The idea is to start from the target node (N - 1) and
// add to the queue those nodes that lead to the minimum cost in the preceeding
// node
int bfs(int s, int t)
{
	int pathLength = 0;

	queue<int> q;
	q.push(s);

	while (!q.empty())
	{
		int cn = q.front();

		if (!visited[cn])
		{
			map<int, pair<V, int> >::iterator it = A[cn].begin();

			for (; it != A[cn].end(); ++it)
			{
				int sn = it->first;

				// if the minimum cost of the sibling node (sn) plus the edge
				// to the current node (cn) is equal to the minimum cost of cn,
				// then add the cost of the edge to the length of the path
				// --> why? if this condition holds, it means that this edge
				// belongs to a shortest path from 0 to N - 1
				if (z[sn] + it->second.first == z[cn])
				{
					// there may be multiple paths from a node
					// to another with the same length
					pathLength += (it->second.first * it->second.second);

					if (sn != t)
					{
						q.push(sn);
					}
				}
			}

			visited[cn] = true;
		}

		q.pop();
	}

	return pathLength;
}

void addEdge(int p1, int p2, int l)
{
	map<int, pair<V, int> >& m = A[p1];
	map<int, pair<V, int> >::iterator it = m.find(p2);

	if (it != m.end())
	{
		if (it->second.first == l)
		{
			++(it->second.second);
		}
		else if (it->second.first > l)
		{
			it->second.first = l;
			it->second.second = 1;
		}
	}
	else
	{
		m[p2] = MP(l, 1);
	}
}

int main()
{
	int t = 0; // number of trails

	while (cin >> N >> t)
	{
		int p1, p2, l;

		for (int i = 0; i < N; ++i)
		{
			A[i].clear();
			z[i] = 1000000000; // initialize cost with big values
			visited[i] = false;
		}

		for (int i = 0; i < t; ++i)
		{
			cin >> p1 >> p2 >> l;

			if (p1 != p2)
			{
				addEdge(p1, p2, l);
				addEdge(p2, p1, l);
			}
		}

		dijkstra(0, N - 1);

		// twice the cost returned by BFS because both sides of the paths
		// must be coveed with flowers
		cout << 2 * bfs(N - 1, 0) << endl;
	}

	return 0;
}

