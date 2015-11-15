#include <iostream>
#include <string>
#include <climits>

using namespace std;

typedef struct
{
    string name;
    int rows, columns;
    int** area;
    int** result;
} SnowBoarder;

void getCost(const SnowBoarder&s, int i, int j)
{
	if (s.result[i][j] != -1)
	{
		return;
	}

	int maxCost = 1;

	// Up
	if (i != 0)
	{
		if (s.area[i][j] > s.area[i-1][j])
		{
			getCost(s, i-1, j);
			int cost = 1 + s.result[i-1][j];
			if (maxCost < cost)
			{
				maxCost = cost;
			}
		}
	}

	// Down
	if (i != s.rows-1)
	{
		if (s.area[i][j] > s.area[i+1][j])
		{
			getCost(s, i+1, j);
			int cost = 1 + s.result[i+1][j];
			if (maxCost < cost)
			{
				maxCost = cost;
			}
		}	
	}

	// Left
	if (j != 0)
	{
		if (s.area[i][j] > s.area[i][j-1])
		{
			getCost(s, i, j-1);
			int cost = 1 + s.result[i][j-1];
			if (maxCost < cost)
			{
				maxCost = cost;
			}
		}	
	}

	// Right
	if (j != s.columns-1)
	{
		if (s.area[i][j] > s.area[i][j+1])
		{
			getCost(s, i, j+1);
			int cost = 1 + s.result[i][j+1];
			if (maxCost < cost)
			{
				maxCost = cost;
			}
		}	
	}

	s.result[i][j] = maxCost;
}

int getLongestRun(const SnowBoarder& s)
{
	int max = INT_MIN;

    for (int i = 0; i < s.rows; ++i)
    {
        for (int j = 0; j < s.columns; ++j)
        {
        	getCost(s, i, j);

        	if (s.result[i][j] > max)
        	{
        		max = s.result[i][j];
        	}
        }
    }
    
    delete [] s.area[0];
    delete s.area;

    delete [] s.result[0];
    delete s.result;

    return max;
}


int main()
{
    int testCases = 0;
    
    cin >> testCases;
    
    for (int i = 0; i < testCases; ++i)
    {
        SnowBoarder s;
        cin >> s.name >> s.rows >> s.columns;
        s.area = new int*[s.rows];
        s.result = new int*[s.rows];

        for (int j = 0; j < s.rows; ++j)
        {
        	s.area[j] = new int[s.columns];
        	s.result[j] = new int[s.columns];
            for (int k = 0; k < s.columns; ++k)
            {
                cin >> s.area[j][k];
                s.result[j][k] = -1;
            }
        }
        
        int maxSteps = getLongestRun(s);
        
        /*for (int i = 0; i < s.rows; ++i)
    	{
	        for (int j = 0; j < s.columns; ++j)
	        {
	        	cout << s.result[i][j] << " ";
	        }
	        cout << endl;
    	}*/

        cout << s.name << ": " << maxSteps << endl;
    }
    
    return 0;
}
