#include <iostream>

using namespace std;

// mappings between ascii chars
char M[128];

int main()
{
	int T = 0;
	cin >> T;
	
	for (int i = 0; i < T; ++i)
	{
		string s = "";
		int R = 0;
		
		cin >> s >> R;
				
		for (int j = 'A'; j <= 'Z'; ++j)
		{
			M[j] = j;
		}
		
		M['_'] = '_';
		
		char ca, cb;
		
		for (int j = 0; j < R; ++j)
		{
			cin >> ca >> cb;
						
			for (int k = 'A'; k <= 'Z'; ++k)
			{
				if (M[k] == cb)
				{
					M[k] = ca;
				}
			}
		}
		
		for (int j = 0; j < s.length(); ++j)
		{
			cout << M[s[j]];
		}
		
		cout << "\n";
	}

	return 0;
}

