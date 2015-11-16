#include <iostream>
#include <set>
#include <sstream>

using namespace std;

set<int> areasLinksArray[101];

int numAreas = 0, originArea = 0, endArea = 0;
char dummyChar = ' ';

int finalMapping[101];

int NUM_ANIMALS = 4;

bool conflictsWithNeighbours(int numAnimal, int numArea)
{
	set<int>& neighbours = areasLinksArray[numArea];

	for (set<int>::iterator it = neighbours.begin(); it != neighbours.end(); ++it)
	{
		if (finalMapping[*it] == numAnimal)
		{
			return true;
		}
	}

	return false;
}

bool isSolutionFound(int numArea)
{
	for (int i = 1; i <= NUM_ANIMALS; ++i)
	{
		if (!conflictsWithNeighbours(i, numArea))
		{
			finalMapping[numArea] = i;

			if (numArea == numAreas)
			{
				return true;
			}

			if (isSolutionFound(numArea + 1))
			{
				return true;
			}
		}
	}

	finalMapping[numArea] = 0;

	return false;
}

int main()
{
	string line = "";

	while (cin >> numAreas)
	{
		for (int i = 1; i <= numAreas; ++i)
		{
			areasLinksArray[i].clear();
			finalMapping[i] = 0;
		}
	
		getline(cin, line);
	
		while (getline(cin, line))
		{
			if (line.length() == 0) break;
		
			stringstream stream(line);
			stream >> originArea >> dummyChar >> endArea;
			
			areasLinksArray[originArea].insert(endArea);
			areasLinksArray[endArea].insert(originArea);		
		}
		
		if (isSolutionFound(1))
		{
			for (int i = 1; i <= numAreas; ++i)
			{
				cout << i << " " << finalMapping[i] << endl;
			}
		}
		else
		{
			cout << "Impossible assignation" << endl;
		}
	}

	return 0;
}