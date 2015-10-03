/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 03/10/2015
 * Time: 0.033
 */
#include <iostream>
#include <map>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

using namespace std;

int A[101][101];
bool V[101];
int N;
map<int, int> nodes; // scanned number -> node number in graph

void floyd_warshall()
{
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				A[i][j] = MIN(A[i][j], A[i][k] + A[k][j]);
}

void clean()
{
	for (int i = 0; i < 101; ++i)
	{
		for (int j = 0; j < 101; ++j)
		{
			A[i][j] = 10000;
		}

		V[i] = false;
	}

	N = 0;
	nodes.clear();
}

double computeMean()
{
	int sum = 0;

	for (int i = 0; i < N; ++i)
	{
		if (V[i])
		{
			for (int j = 0; j < N; ++j)
			{
				if (V[j] && i != j)
				{
					sum += A[i][j];
				}
			}
		}
	}

	double mean = double(sum) / double(N * (N - 1));
	return mean;
}

int main()
{
	int T = 0;
	int n1, n2;

	clean();

	bool newCase = true;

	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(3);

	while (cin >> n1 >> n2)
	{
		if (!n1 && !n2)
		{
			if (newCase)
			{
				break;
			}
			else
			{
				floyd_warshall();
				cout << "Case " << T << ": average length between pages = " << computeMean() << " clicks\n";
				newCase = true;
				clean();
			}
		}
		else
		{
			if (newCase)
			{
				newCase = false;
				++T;
			}

			if (nodes.find(n1) == nodes.end())
			{
				nodes[n1] = N++;
			}

			if (nodes.find(n2) == nodes.end())
			{
				nodes[n2] = N++;
			}

			int n1c = nodes[n1];
			int n2c = nodes[n2];

			if (!V[n1c])
			{
				V[n1c] = true;
			}

			if (!V[n2c])
			{
				V[n2c] = true;
			}

			A[n1c][n2c] = 1;
		}
	}

	return 0;
}

