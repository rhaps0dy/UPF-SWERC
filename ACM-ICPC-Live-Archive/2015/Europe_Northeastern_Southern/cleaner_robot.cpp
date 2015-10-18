#include <iostream>
#include <utility>

using namespace std;

int W; // width
int H; // height
pair<int, int> P; // position
char O; // orientation
char M[11][11]; // room map
char C[11][11]; // cleaned map
int NC = 0; // number cleaned cells

void move() // return if rotated
{
	if (O == 'U')
	{
		if (P.first > 0 && M[P.first - 1][P.second] != '*')
		{
			--P.first;
		}
		else
		{
			O = 'R';
		}
	}
	else if (O == 'R')
	{
		if (P.second < H - 1 && M[P.first][P.second + 1] != '*')
		{
			++P.second;
		}
		else
		{
			O = 'D';
		}
	}
	else if (O == 'D')
	{
		if (P.first < W - 1 && M[P.first + 1][P.second] != '*')
		{
			++P.first;
		}
		else
		{
			O = 'L';
		}
	}
	else if (O == 'L')
	{
		if (P.second > 0 && M[P.first][P.second - 1] != '*')
		{
			--P.second;
		}
		else
		{
			O = 'U';
		}
	}	
}

void cleanCurrentPosition()
{
	if (C[P.first][P.second] == '.')
	{
		C[P.first][P.second] = O;
		++NC;
	}	
}

bool isAllPossibleCleaned()
{
	if (C[P.first][P.second] == '.')
	{
		return false;
	}
	else
	{
		if (C[P.first][P.second] != O)
		{
			return false;
		}
	}
	
	return true;
}

int main()
{
	while (cin >> W >> H)
	{
		NC = 0;
		
		char c = ' ';
		
		for (int i = 0; i < W; ++i)
		{
			for (int j = 0; j < H; ++j)
			{
				cin >> c;
				
				if (c == 'U' || c == 'R' || c == 'D' || c == 'L')
				{
					M[i][j] = '.';
					P.first = i;
					P.second = j;
					O = c;
				}
				else
				{
					M[i][j] = c;
				}
				
				C[i][j] = '.';
			}
		}
		
		while (!isAllPossibleCleaned())
		{
			cleanCurrentPosition();
			move();
		}
		
		cout << NC << endl;
	}
	
	return 0;
}
