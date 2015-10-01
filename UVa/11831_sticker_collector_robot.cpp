/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 01/10/2015
 * Time: 0.056
 */
#include <iostream>

using namespace std;

int N; // rows
int M; // columns
int S; // number of movements
char T[101][101]; // table

char changeOrientation(char ori, char rot)
{
	if (ori == 'N') // north
	{
		if (rot == 'D')	return 'L';
		else if (rot == 'E') return 'O';
	}
	else if (ori == 'S') // south
	{
		if (rot == 'D')	return 'O';
		else if (rot == 'E') return 'L';
	}
	else if (ori == 'L') // east
	{
		if (rot == 'D')	return 'S';
		else if (rot == 'E') return 'N';
	}
	else if (ori == 'O') // west
	{
		if (rot == 'D')	return 'N';
		else if (rot == 'E') return 'S';
	}
	
	return ' ';
}

int moveForward(int& x, int& y, char ori)
{
	int nstickers = 0;
	
	if (ori == 'N')
	{
		int nx = x - 1;
		
		if (nx < 0 || T[nx][y] == '#')
		{
			nx = x;
		}
		else if (T[nx][y] == '*')
		{
			++nstickers;
			T[nx][y] = '.';
		}
		
		x = nx;
	}
	else if (ori == 'S')
	{
		int nx = x + 1;
		
		if (nx >= N || T[nx][y] == '#')
		{
			nx = x;
		}
		else if (T[nx][y] == '*')
		{
			++nstickers;
			T[nx][y] = '.';
		}
		
		x = nx;
	}
	else if (ori == 'L')
	{
		int ny = y + 1;
		
		if (ny >= M || T[x][ny] == '#')
		{
			ny = y;
		}
		else if (T[x][ny] == '*')
		{
			++nstickers;
			T[x][ny] = '.';
		}
		
		y = ny;
	}
	else if (ori == 'O')
	{
		int ny = y - 1;
		
		if (ny < 0 || T[x][ny] == '#')
		{
			ny = y;
		}
		else if (T[x][ny] == '*')
		{
			++nstickers;
			T[x][ny] = '.';
		}
		
		y = ny;
	}
	
	return nstickers;
}

int main()
{
	while (cin >> N >> M >> S)
	{
		if (!N && !M && !S) break;
	
		char c = ' ';
	
		int initi = 0, initj = 0;
		char ori = ' ';
	
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				cin >> c;
				
				if (c == '.' || c == '*' || c == '#')
				{
					T[i][j] = c;
				}
				else
				{
					initi = i;
					initj = j;
					ori = c;
					T[i][j] = '.';
				}
			}
		}
		
		char mov = ' ';
		int nstickers = 0;
		
		for (int k = 0; k < S; ++k)
		{
			cin >> mov;
			
			if (mov == 'F')
			{
				nstickers += moveForward(initi, initj, ori);
			}
			else
			{
				ori = changeOrientation(ori, mov);
			}
		}
		
		cout << nstickers << endl;
	}

	return 0;
}

