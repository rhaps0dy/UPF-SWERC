#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

int table[8][8];
int queens[8];
int maxnum = 0;

bool isCollision(int i, int j)
{
	return ((queens[i] == queens[j]) || (abs(i -j) == abs(queens[i] - queens[j])));
}

void findMax(int q)
{
	if (q == 8)
	{
		int n = 0;

		for (int i = 0; i < 8; ++i)
		{
			n += table[queens[i]][i];
		}

		maxnum = max(maxnum, n);
/*
cout << maxnum << endl;

			for (int z = 0; z < 8; ++z) cout << queens[z] << " ";

			cout << endl;

cout << endl;
*/
	}
	else
	{
		for (int i = 0; i < 8; ++i)
		{
			queens[q] = i;

			bool collides = false;

			for (int j = 0; j < q && !collides; ++j)
			{
				collides = isCollision(q, j);
			}

			if (!collides)
			{
				findMax(q + 1);
			}
		}
	}
}

int main()
{
	int T = 0; // num tables

	while (cin >> T)
	{
		for (int i = 0; i < 8; ++i)
		{
			queens[i] = 0;
		}

		for (int i = 0; i < T; ++i)
		{
			maxnum = 0;

			for (int j = 0; j < 8; ++j)
			{
				for (int k = 0; k < 8; ++k)
				{
					cin >> table[j][k];
				}
			}

			findMax(0);

			cout << setw(5) << right << maxnum << endl;
		}
	}

	return 0;
}

