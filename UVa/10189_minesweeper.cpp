#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int iVar[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int jVar[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
const int MAX_SURROUND = 8;

void assignNumber(int i, int j, vector<string>& mineTable)
{
	int coeficient = 0;

	for (unsigned k = 0; k < MAX_SURROUND; ++k)
	{
		int iprime = i + iVar[k];
		int jprime = j + jVar[k];

		if (iprime >= 0 && iprime < mineTable.size())
		{
			string rowStr = mineTable[iprime];

			if (jprime >= 0 && jprime < rowStr.length())
			{
				if (rowStr[jprime] == '*')
				{
					++coeficient;
				}
			}
		}
	}

	mineTable[i][j] = (char)((int)'0' + coeficient);
}

int main()
{
	int rows = 0, cols = 0;
	int field = 1;

	while (cin >> rows >> cols)
	{
		if (!rows && !cols)
			break;

		if (field != 1)
			cout << endl;

		vector<string> mineTable;
		string rowStr = "";
		getline(cin, rowStr);

		// get table
		for (int i = 0; i < rows; ++i)
		{
			getline(cin, rowStr);
			mineTable.push_back(rowStr);
		}

		// assign points
		for (int i = 0; i < rows; ++i)
		{
			string rowStr = mineTable[i];

			for (int j = 0; j < cols; ++j)
			{
				if (rowStr[j] != '*')
				{
					assignNumber(i, j, mineTable);
				}
			}
		}

		// print
		cout << "Field #" << field << ":" << endl;
		for (int i = 0; i < rows; ++i)
		{
			cout << mineTable[i] << endl;
		}

		++field;
	}

	return 0;
}
