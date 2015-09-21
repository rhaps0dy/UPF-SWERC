/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 21/09/2015
 * Time: 0.003
 */
#include <iostream>

#define MAX_SEQUENCE 20

using namespace std;

int P = 0; // period of the patterns
int RP[8]; // repeated pattern
char S[MAX_SEQUENCE];
char lastChar = 'A';
int ch = 0; // current height index

int main()
{
	while (cin >> P)
	{
		if (P == 0) break;

		for (int i = 0; i < MAX_SEQUENCE; ++i)
		{
			S[i] = '!';
		}

		S[0] = 'A';
		lastChar = 'A';

		for (int i = 0; i < P; ++i)
		{
			cin >> RP[i];
		}

		bool crashed = false;

		for (int i = 0; i < MAX_SEQUENCE; ++i)
		{
			ch = i % P;

			char ball = S[i];

			if (ball == '!')
			{
				ball = ++lastChar;
				S[i] = ball;
			}

			int target = i + RP[ch];

			if (target < MAX_SEQUENCE)
			{
				if (S[target] == '!')
				{
					S[target] = ball;
				}
				else
				{
					crashed = true;
					break;
				}
			}
		}

		if (crashed)
		{
			cout << "CRASH" << endl;
		}
		else
		{
			for (int i = 0; i < MAX_SEQUENCE; ++i)
			{
				cout << S[i];
			}

			cout << endl;
		}
	}

	return 0;
}

