/**
 * Author: Daniel Furelos (Ertsiger)
 * 04/10/2015
 * Time: 0.223
 */
#include <iostream>
#include <utility>
#include <queue>

using namespace std;

int R, C; // rows and columns
int A[1001][1001];
int V[1001][1001];

int getNumSteps(const pair<int, int>& origin, const pair<int, int>& end)
{
	if (origin == end)
	{
		return 0;
	}

	queue< pair< pair<int, int>, int> > q;
	q.push(make_pair(origin, 0));

	V[origin.first][origin.second] = true;

	while (!q.empty())
	{
		pair< pair<int, int>, int>& p = q.front();
		int icoord = p.first.first;
		int jcoord = p.first.second;

		int jleft = jcoord - 1;

		if (jleft >= 0 && !V[icoord][jleft] && A[icoord][jleft] != 1)
		{
			pair<int, int> np(icoord, jleft);

			if (np == end)
			{
				return p.second + 1;
			}
			else
			{
				V[icoord][jleft] = true;
				q.push(make_pair(np, p.second + 1));
			}
		}

		int jright = jcoord + 1;

		if (jright < C && !V[icoord][jright] && A[icoord][jright] != 1)
		{
			pair<int, int> np(icoord, jright);

			if (np == end)
			{
				return p.second + 1;
			}
			else
			{
				V[icoord][jright] = true;
				q.push(make_pair(np, p.second + 1));
			}
		}

		int iup = icoord - 1;

		if (iup >= 0 && !V[iup][jcoord] && A[iup][jcoord] != 1)
		{
			pair<int, int> np(iup, jcoord);

			if (np == end)
			{
				return p.second + 1;
			}
			else
			{
				V[iup][jcoord] = true;
				q.push(make_pair(np, p.second + 1));
			}
		}

		int idown = icoord + 1;

		if (idown < R && !V[idown][jcoord] && A[idown][jcoord] != 1)
		{
			pair<int, int> np(idown, jcoord);

			if (np == end)
			{
				return p.second + 1;
			}
			else
			{
				V[idown][jcoord] = true;
				q.push(make_pair(np, p.second + 1));
			}
		}

		q.pop();
	}

	return -1;
}

int main()
{
	while (cin >> R >> C)
	{
		if (!R && !C) break;

		for (int i = 0; i < 1001; ++i)
		{
			for (int j = 0; j < 1001; ++j)
			{
				A[i][j] = 0;
				V[i][j] = false;
			}
		}

		int b = 0, r = 0, numcols = 0, c = 0;
		cin >> b;

		for (int i = 0; i < b; ++i)
		{
			cin >> r >> numcols;

			for (int j = 0; j < numcols; ++j)
			{
				cin >> c;
				A[r][c] = 1;
			}
		}

		int x0, y0, xf, yf;
		cin >> x0 >> y0 >> xf >> yf;

		pair<int, int> origin(x0, y0);
		pair<int, int> end(xf, yf);

		cout << getNumSteps(origin, end) << endl;
	}

	return 0;
}

