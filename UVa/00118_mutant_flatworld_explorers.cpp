#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isInLostCell(int robotX, int robotY, const vector<int>& lostCells)
{
	for (unsigned int i = 0; i < lostCells.size(); i += 2)
	{
		if (lostCells[i] == robotX && lostCells[i+1] == robotY)
			return true;
	}

	return false;
}

void setNewPosition(int& x, int& y, char& orient, const char& movement)
{
	if (movement == 'F')
	{
		if (orient == 'N') ++y;
		else if (orient == 'E') ++x;
		else if (orient == 'S') --y;
		else if (orient == 'W') --x;
	}
	else if (movement == 'R')
	{
		if (orient == 'N') orient = 'E';
		else if (orient == 'E') orient = 'S';
		else if (orient == 'S') orient = 'W';
		else if (orient == 'W') orient = 'N';
	}
	else if (movement == 'L')
	{
		if (orient == 'N') orient = 'W';
		else if (orient == 'E') orient = 'N';
		else if (orient == 'S') orient = 'E';
		else if (orient == 'W') orient = 'S';
	}
}

int main()
{
	vector<int> lostCells;

	int rows = 0;
	int columns = 0;

	int robotX = 0;
	int robotY = 0;
	char robotOr = ' ';
	string movSeq = "";

	bool lost = false;

	int oldX = 0;
	int oldY = 0;
	char oldOr = ' ';

	cin >> rows >> columns;

	while (cin >> robotX >> robotY >> robotOr >> movSeq)
	{
		for (int i = 0; i < movSeq.length(); ++i)
		{
			oldX = robotX;
			oldY = robotY;
			oldOr = robotOr;

			setNewPosition(robotX, robotY, robotOr, movSeq[i]);

			if (robotX > rows || robotX < 0 || robotY > columns || robotY < 0)
			{
				if (isInLostCell(oldX, oldY, lostCells))
				{
					robotX = oldX;
					robotY = oldY;
					robotOr = oldOr;				
				}
				else
				{
					lost = true;
					lostCells.push_back(oldX);
					lostCells.push_back(oldY);
					break;
				}
			}
		}

		if (lost)
		{
			cout << oldX << " " << oldY << " " << oldOr << " LOST" << endl;
			lost = false;
		}
		else
		{
			cout << robotX << " " << robotY << " " << robotOr << endl;
		}
	}

	return 0;
}
