/**
 * Author: Daniel F.B. (Ertsiger)
 * 12/10/2015
 * Time: 0.003
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

set<int> A[101]; // adjacency list (directed graph without cycles)
int inbound[101]; // number of nodes that point to each node
vector<int> fo; // final order

void toposort(int N) {
	set<int> order;
	int current;

	// Search for roots
	for (int m = 0; m < N; m++){
		if (inbound[m] == 0)
			order.insert(m);
	}

	// Start topsort from roots
	while (!order.empty()){
		// Pop from stack 
		current = *(order.begin());
		order.erase(order.begin());
		// Save order in fo
		fo.push_back(current);
		// Add childs only if inbound is 0
		for (auto it = A[current].begin(); it != A[current].end(); ++it)
		{
			inbound[*it]--;
			if (inbound[*it] == 0)
				order.insert(*it);
		}
	}
}

int main()
{
	int N, M;
	int C = 1;

	string names[101];

	while (cin >> N)
	{
		fo.clear();

		for (int i = 0; i <= N; ++i)
		{
			A[i].clear();
			inbound[i] = 0;
			names[i] = "";
		}

		string bev = "";
		map<string, int> beverages;

		for (int i = 0; i < N; ++i)
		{
			cin >> bev;
			beverages[bev] = i;
			names[i] = bev;
		}

		cin >> M;
		string bev1 = "", bev2 = "";
		int bev1i = 0, bev2i = 0;

		for (int i = 0; i < M; ++i)
		{
			cin >> bev1 >> bev2;
			bev1i = beverages[bev1];
			bev2i = beverages[bev2];

			if (A[bev1i].find(bev2i) == A[bev1i].end())
			{
				A[bev1i].insert(bev2i);
				++inbound[bev2i];
			}
		}

		// we use a queue inside to priorize those nodes with lower identifiers
		// since they are the first ones in the input
		toposort(N);

		cout << "Case #" << C << ": Dilbert should drink beverages in this order:";

		for (int i = 0; i < fo.size(); ++i)
		{
			cout << " " << names[fo[i]];
		}

		cout << ".\n\n";

		++C;
	}

	return 0;
}