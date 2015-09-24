/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 24/09/2015
 * Time: 0.139
 */

#include <iostream>

#define LL long long

using namespace std;

/**
 * c^2 = a^2 + b^2 can be rewritten as a^2 = c^2 - b^2, then
 * a^2 = (c - b) * (c + b). The last expression can be rewritten
 * as a^2 = x * y, where x = c - b and y = c + b. We use the previous
 * equations to find out that c = (x + y) / 2, and that b = (y - x) / 2.
 * 
 * The lower term 'x' cannot be higher than 'a' since the other
 * term (y) will always be higher than 'x', so it cannot result in a^2.
 *
 * Then, we must look for a value of 'x' between 1 and 'a' such that a^2
 * is divisible by 'x'. Then, we find a value of 'b' by checking first that
 * (y - x) is divisible by two (we wanted to guarantee integer values). Finally,
 * once we have a valid 'b', we check it is greater than 'a'.
 */
int main()
{
	LL a = 0;
	
	while (cin >> a)
	{
		if (a == 0) break;
		
		LL a2 = a * a;
		
		LL n = 0;
		
		for (LL x = 1; x <= a; ++x)
		{
			if (a2 % x == 0)
			{
				LL y = a2 / x;
				
				if (((y - x) % 2) == 0)
				{
					LL b = (y - x) / 2;
					
					if (b > a)
					{
						++n;
					}
				}
			}
		}
		
		cout << n << endl;
	}

	return 0;
}

