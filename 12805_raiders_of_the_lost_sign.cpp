/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 21/09/2015
 * Time: 0.942
 */

#include <iostream>

#define MAX_NUM 100001

using namespace std;

int v[MAX_NUM]; // primes
bool signs[MAX_NUM]; // signs of the numbers (true -> +, false -> -)

void savePrimes()
{
	// save all primes between 2 and MAX_NUM in v
	int k = 0;

	v[k++] = 2;

	for (int i = 3; i < MAX_NUM; i += 2)
	{
		bool b = true;

		for (int j = 0; b && v[j] * v[j] <= i; j++)
		{
			b = i%v[j] > 0;
		}

		if (b)
		{
			v[k++] = i;
		}
	}
}

bool isPrime(int x)
{
	bool prime = true;

	for (int j = 0; prime && v[j] * v[j] <= x; j++)
	{
		prime = x%v[j] > 0;
	}

	return prime;
}

void saveSigns()
{
	bool posSign = true;

	for (int i = 2; i < MAX_NUM; ++i)
	{
		posSign = true;

		// You put + if the denominator of the fraction is 2.
		if (i == 2)
		{
			posSign = true;
		}
		else
		{
			if (isPrime(i))
			{
				// You put + if the denominator of the fraction is a prime like
				// 4m - 1, for some integer m
				if (((i + 1) % 4) == 0)
				{
					posSign = true;
				}
				else if (((i - 1) % 4) == 0)
				{
					posSign = false;
				}
			}
			else
			{
				// If the denominator is not a prime number, you put the sign
				// resultant of multiplying the signs corresponding to each 
				// prime factor.
				int n = i;

				for (int j = 2; j <= n; ++j)
				{
					while (n % j == 0)
					{
						n /= j;
						posSign = ((posSign & signs[j]) | (!posSign & !signs[j]));
					}
				}
			}
		}

		signs[i] = posSign;
	}
}

int main()
{
	savePrimes();
	saveSigns();

	int t = 0;
	cin >> t;

	for (int i = 0; i < t; ++i)
	{
		int x = 0;

		while (cin >> x)
		{
			if (signs[x])
			{
				cout << "+\n";
			}
			else
			{
				cout << "-\n";
			}
		}
	}

	return 0;
}

