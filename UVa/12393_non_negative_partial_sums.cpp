#include <iostream>

using namespace std;

long N;
int A[1000001];
bool B[1000001];

int main()
{
	while (cin >> N)
	{
		if (N == 0) break;

		bool allPositive = true;
		bool allNegative = true;

		for (long i = 0; i < N; ++i)
		{
			cin >> A[i];

			if (A[i] >= 0)
			{
				allNegative = false;
			}
			else
			{
				allPositive = false;
			}

			B[i] = true;
		}

		if (allPositive) cout << N << endl;
		else
		if (allNegative) cout << 0 << endl;
		else
		{
			bool loop = true; // indicar si se ha dado la vuelta

			for (long i = N-1, j; loop && i >= 0; --i)
			{
				if (A[i] < 0)
				{
					B[i] = false;

					long sum = A[i];

					for (j = i - 1; sum < 0 && j != i; --j)
					{
						if (j < 0)
						{
							loop = false;

							if (i + 1 == N) break;

							j = N - 1;
						}

						sum += A[j];

						if (sum < 0)
						{
							B[j] = false;
						}
					}

					i = j + 1;
				}
			}

			long nnps = 0;

			for (long i = 0; i < N; ++i)
			{
				if (B[i]) ++nnps;
			}

			cout << nnps << endl;
		}
	}

	return 0;
}
