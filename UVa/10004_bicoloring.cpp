/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 01/10/2015
 * Time: 0.000s
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N; // nodes
int E; // edges
vector<int> A[201]; // adjacency list
int C[201]; // colours list

int main()
{
	while (cin >> N)
	{
		if (N == 0)
			break;
		
		for (int i = 0; i < N; ++i)
		{
			A[i].clear();
			C[i] = -1;
		}
		
		cin >> E;
		
		int n1, n2;
		
		for (int i = 0; i < E; ++i)
		{
			cin >> n1 >> n2;
			A[n1].push_back(n2);
			A[n2].push_back(n1);
		}
		
		int color = 0;
		C[0] = color;
		
		bool bicolored = true;
		
		queue<int> q;
		q.push(0);
		
		while (!q.empty() && bicolored)
		{
			int n = q.front();
			color = C[n];
			
			int newColor = color == 0 ? 1 : 0;
			
			for (int i = 0; i < A[n].size(); ++i)
			{
				int m = A[n][i];
				
				if (C[m] == -1)
				{
					C[m] = newColor;
					q.push(m);
				}
				else if (C[m] == color)
				{
					bicolored = false;
					break;
				}
			}
			
			q.pop();
		}
		
		if (bicolored)
		{
			cout << "BICOLORABLE.\n";
		}
		else
		{
			cout << "NOT BICOLORABLE.\n";
		}
	}

	return 0;
}

