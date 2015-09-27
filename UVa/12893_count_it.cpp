/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 24/09/2015
 * Time: 0.000
 */

#include <iostream>

#define LL long long

using namespace std;

int main()
{
	int T = 0;
	cin >> T;
	
	LL n = 0;
	
	while (T-- > 0)
	{
		cin >> n;
		
		int r = 0;
		
		if (n == 1)
		{
			r = 1;
		}
		else if (n > 1)
		{
			while (n >= 1)
			{
				if (n % 2 != 0)
				{
					++r;
				}
				
				n /= 2;
			}
		}
		
		cout << r << endl;
	}
	
	return 0;
}

