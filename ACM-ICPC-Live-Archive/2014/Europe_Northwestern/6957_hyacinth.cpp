/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 07/10/2015
 * Time: 0.328
 */
#include <iostream>
#include <vector>

using namespace std;

int N = 0; // number of nodes in the network
vector<int> A[10001]; // adjacency list
int F1[10001]; // frequency 1 for each node
int F2[10001]; // frequency 2 for each node
bool F[10001]; // whether a frequency has been used or not
int LFA = 1; // last frequency assigned

int getUnusedFrequency(int n)
{
	int f1 = F1[n];
	int f2 = F2[n];

	if (!F[f1]) return f1;
	if (!F[f2]) return f2;

	return f1; // does not matter which frequency is assigned
}

void f(int prev, int cur)
{
	if (F1[cur] == -1) F1[cur] = LFA++;
	if (F2[cur] == -1) F2[cur] = LFA++;

	for (int i = 0; i < A[cur].size(); ++i)
	{
		int next = A[cur][i];

		if (next != prev)
		{
			int freq = getUnusedFrequency(cur);
			F1[next] = freq;
			F[freq] = true;
			f(cur, next);
		}
	}
}

int main()
{
	while (cin >> N)
	{
		int n1, n2;

		// Restore variables
		for (int i = 0; i < LFA; ++i)
		{
			F[i] = false;
		}

		LFA = 1;

		for (int i = 0; i < N; ++i)
		{
			A[i].clear();
			F1[i] = -1;
			F2[i] = -1;
		}

		// Read input
		for (int i = 0; i < N - 1; ++i)
		{
			cin >> n1 >> n2;
			--n1; --n2;
			A[n1].push_back(n2);
			A[n2].push_back(n1);
		}

		if (N == 2) // particular case
		{
			cout << "1 2\n1 2\n";
		}
		else
		{
			f(-1, 0);

			for (int i = 0; i < N; ++i)
			{
				cout << F1[i] << " " << F2[i] << endl;
			}
		}

		cout << endl;
	}

	return 0;
}

