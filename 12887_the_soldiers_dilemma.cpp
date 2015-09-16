#include <iostream>

using namespace std;

/* Why use Catalan numbers? (Wikipedia)
 *  Cn is the number of permutations of {1, ..., n} 
 *  that avoid the pattern 123 (or any of the other
 *  patterns of length 3); that is, the number of permutations
 *  with no three-term increasing subsequence. For n = 3, these 
 *  permutations are 132, 213, 231, 312 and 321. For n = 4, they 
 *  are 1432, 2143, 2413, 2431, 3142, 3214, 3241, 3412, 3421, 4132, 
 *  4213, 4231, 4312 and 4321.
 */

// http://stackoverflow.com/questions/10042195/calculating-catalan-numbers-mod-prime-number

#define MAX_SOLDIERS 5001
#define MOD 1000000007

unsigned long long v[MAX_SOLDIERS];

/*
void catalan()
{
	v[0] = 1;
	for (int i = 1; i < MAX_SOLDIERS; ++i)
	{
		v[i] = 2 * i - 1;
		v[i] = v[i] * 2;
		v[i] = (v[i] * v[i-1]) % MOD;
		v[i] = v[i] / (i + 1);
		v[i] = v[i] % MOD;
	}
}*/

void catalan()
{
	v[0] = 1;
	
	for (int i = 1; i < MAX_SOLDIERS; ++i)
	{
		unsigned long long sum = 0;
		for (int j = 0; j < i; ++j)
		{
			sum = (sum + (((v[j] % MOD) * (v[i-j-1] % MOD)) % MOD)) % MOD;
		}

		v[i] = sum % MOD;
	}
}

int main()
{
	catalan();

	int T = 0, N = 0;
	cin >> T;
	
	for (int i = 0; i < T; ++i)
	{
		cin >> N;
		cout << v[N] << "\n";
	}
	
	return 0;
}

