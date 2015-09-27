/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 27/09/2015
 * Time: 0.000
 */
#include <iostream>

using namespace std;

int v[10000];

void generatePrimes()
{
	// save all primes between 2 and 10010 in v
	int k = 0;
	v[k++] = 2;
	
	for (int i = 3; i <= 10010; i += 2)
	{
		bool b = true;
		for (int j = 0; b && v[j]*v[j] <= i; j++)
			b = i%v[j] > 0;
		if (b) v[k++] = i;
	}
}

bool isPrime(int x)
{
	// test whether a number x <= 100000000 is prime
	bool prime = true;
	for (int j = 0; prime && v[j]*v[j] <= x; j++)
		prime = x%v[j] > 0;
	
	return prime;
}

bool isPalindrome(int x)
{
	int n = x;
	int rev = 0;
	
	while (n > 0)
	{
		int dig = n % 10;
		rev = rev * 10 + dig;
		n /= 10;
	}
	
	return rev == x;
}

int main()
{
	int N = 0;
	
	generatePrimes();
	
	while (cin >> N)
	{		
		cout << 2 * N << endl;
		
		if (isPrime(N) && isPalindrome(N))
		{
			break;
		}
	}
	
	return 0;
}

