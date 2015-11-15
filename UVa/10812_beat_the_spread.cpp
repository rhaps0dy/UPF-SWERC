/**
 * Problem 10812
 * DanielFB93
 * 22/04/2014
 */

#include <iostream>

using namespace std;

int main()
{
	int resultLocal = 0;
	int resultVisitant = 0;
	int absDiff = 0;
	int currDiff = 0;
	int resultsSum = 0;
	int numBets = 0;

	bool turnLocal = false;

	cin >> numBets;

	for (unsigned int i = 0; i < numBets; ++i)
	{
		cin >> resultsSum;
		cin >> absDiff;

		if (absDiff > resultsSum || absDiff+1 == resultsSum)
		{
			cout << "impossible" << endl;
		}
		else
		{
			currDiff = resultLocal = resultsSum;
			resultVisitant = 0;
			turnLocal = false;

			while (currDiff > absDiff)
			{
				if (turnLocal) --resultLocal;
				else ++resultVisitant;

				turnLocal = !turnLocal;

				--currDiff;
			}

			if ((resultLocal + resultVisitant) != resultsSum)
			{
				cout << "impossible" << endl;
			}
			else
			{
				cout << resultLocal << " " << resultVisitant << endl;
			}
		}
	}
	return 0;
}