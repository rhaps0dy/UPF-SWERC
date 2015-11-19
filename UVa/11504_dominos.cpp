/**
 * Author: Daniel F.B. (Ertsiger)
 * 19/11/2015
 * Time: 0.375
 */
#include <iostream>
#include <vector>
#include <map>

#define MIN(a,b) ((a)<(b)?(a):(b))

using namespace std;

// Tarjan variables
int index, ct;
bool I[100001];
int D[100001], L[100001];
vector<int> S;
vector<int> V[100001]; // listas de adyacencia

int N; // num nodes
int M; // num edges

void tarjan(unsigned n) {
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
	fill(I, I + N, false);
	fill(D, D + N, -1);
	S.clear();
	for (unsigned n = 0; n < N; ++n)
		if (D[n] < 0)
			tarjan(n);
	// ct = numero total de scc
}

int main()
{
	int T;
	cin >> T;

	while (T--)
	{
		int x, y;
		cin >> N >> M;

		for (int i = 0; i < N; ++i)
		{
			V[i].clear();
		}

		for (int i = 0; i < M; ++i)
		{
			cin >> x >> y;
			V[x - 1].push_back(y - 1);
		}

		scc();

		map<int, int> inDegree;

		for (int i = 0; i < N; ++i)
		{
			if (inDegree.find(L[i]) == inDegree.end())
			{
				inDegree[L[i]] = 0;
			}
		}

		for (int i = 0; i < N; ++i)
		{
			int x = i;

			for (int j = 0; j < V[i].size(); ++j)
			{
				int y = V[i][j];

				if (L[x] != L[y])
				{
					inDegree[L[y]]++;
				}
			}
		}

		int count = 0;
		for (auto it = inDegree.begin(); it != inDegree.end(); ++it)
		{
			if (it->second == 0)
			{
				count++;
			}
		}

		cout << count << endl;
	}

	return 0;
}

