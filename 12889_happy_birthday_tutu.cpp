#include <iostream>

using namespace std;

int main()
{
	int T = 0, K = 0, Ai = 0, Ai_temp = 0;
	
	cin >> T;
	
	for (int i = 0; i < T; ++i)
	{
		cin >> K;
		
		bool allEqual = true;

		Ai = -1;
		
		for (int j = 0; j < K; ++j)
		{
			cin >> Ai_temp;

			if (j > 0 && Ai_temp != Ai)
			{
				allEqual = false;
			}
			
			Ai = Ai_temp;
		}
		
		if (allEqual)
		{
			cout << "Better luck next time!\n";
		}
		else
		{
			cout << "Happy Birthday Tutu!\n";
		}
	}

	return 0;
}

