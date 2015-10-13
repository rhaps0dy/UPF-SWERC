/**
 * Author: Daniel F.B. (Ertsiger)
 * 13/10/2015
 * Time: 0.000
 */
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<int> A[21]; // adjacency list (directed graph without cycles)
int inbound[21]; // number of nodes that point to each node
bool visited[21]; // number of visited nodes
int N; // number of identifiers/nodes
int S[21]; // current sequence of
char idToSymb[21]; // int identifiers to char symbols they represent
int numSol = 0;

void f(int numAssignedChars)
{
	if (numAssignedChars == N)
	{
		bool first = true;

		for (int i = 0; i < N; ++i)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				cout << " ";
			}

			cout << idToSymb[S[i]];
		}

		cout << endl;

		++numSol;
	}
	else
	{
		for (int i = 0; i < N; ++i)
		{
			if (inbound[i] == 0 && !visited[i])
			{
				visited[i] = true;
				S[numAssignedChars] = i;

				for (int j = 0; j < A[i].size(); ++j)
				{
					--inbound[A[i][j]];
				}

				f(numAssignedChars + 1);

				for (int j = 0; j < A[i].size(); ++j)
				{
					++inbound[A[i][j]];
				}

				visited[i] = false;
			}
		}
	}
}

int main()
{
	int T = 0;
	cin >> T;

	string useless = "", symbols = "", order = "";
	getline(cin, useless);

	while (T--)
	{
		numSol = 0;

		for (int i = 0; i < 21; ++i)
		{
			A[i].clear();
			inbound[i] = 0;
			visited[i] = false;
		}

		// get input
		getline(cin, useless);
		getline(cin, symbols);
		getline(cin, order);

		// first line of input
		stringstream symbols_ss(symbols);
		map<char, int> symbToId;

		char c = ' ';
		int currId = 0;

		while (symbols_ss >> c)
		{
			if (symbToId.find(c) == symbToId.end())
			{
				symbToId[c] = currId;
				idToSymb[currId] = c;
				++currId;
			}
		}

		N = currId;

		// second line of input
		stringstream order_ss(order);
		char lhs, op, rhs;

		while (order_ss >> lhs >> op >> rhs)
		{
			int lhsi = symbToId[lhs];
			int rhsi = symbToId[rhs];

			if (find(A[lhsi].begin(), A[lhsi].end(), rhsi) == A[lhsi].end())
			{
				A[lhsi].push_back(rhsi);
				++inbound[rhsi];
			}
		}

		f(0);

		if (numSol == 0)
		{
			cout << "NO\n";
		}
		
		if (T > 0)
			cout << "\n";
	}

	return 0;
}

