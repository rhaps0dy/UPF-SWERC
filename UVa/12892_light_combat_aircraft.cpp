/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 24/09/2015
 * Time: 0.163
 */
#include <iostream>
#include <vector>

using namespace std;

vector<int> nodes[10001];
int numChild[10001];

void setNumChild(int n)
{
	numChild[n] = nodes[n].size();

	for (int i = 0; i < nodes[n].size(); ++i)
	{
		int id = nodes[n][i];
		setNumChild(id);
		numChild[n] += numChild[id];
	}
}

int getLca(int n)
{
	int lca = numChild[n];

	if (lca != 0)
	{
		for (int i = 0; i < nodes[n].size() - 1; ++i)
		{
			int id1 = nodes[n][i];

			for (int j = i + 1; j < nodes[n].size(); ++j)
			{
				int id2 = nodes[n][j];
				lca += ((numChild[id1] + 1) * (numChild[id2] + 1));
			}
		}
	}

	return lca;
}

int main()
{
	int T = 0, N = 0, parent = 0;

	cin >> T;

	for (int t = 1; t <= T; ++t)
	{
		cin >> N;

		for (int i = 0; i <= N; ++i)
		{
			nodes[i].clear();
			numChild[i] = 0;
		}

		for (int i = 1; i <= N; ++i)
		{
			cin >> parent;
			nodes[parent].push_back(i);
		}

		for (int i = 0; i < nodes[0].size(); ++i)
		{
			setNumChild(nodes[0][i]);
		}

		cout << "Forest#" << t << ":";

		for (int i = 1; i <= N; ++i)
		{
			int lca = getLca(i);
			cout << " " << lca;
		}

		cout << "\n";
	}

	return 0;
}

