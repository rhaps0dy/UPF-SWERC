#include <iostream>
#include <cmath>

#define MAX_CITIES 500000
#define MAX_POP 5000000

using namespace std;

long cities[MAX_CITIES];
long N, B;

bool isValid(long v)
{
	long boxes = 0;

	for (int i = 0; (i < N) && (boxes <= B); ++i)
	{
		boxes += ceil((long double)cities[i] / (long double)v);
	}

	return (boxes <= B);
}

long getMaxPeoplePerBallot()
{
	long l = 1; // lower limit
	long u = MAX_POP; // upper limit

	while (l+1 < u)
	{
		long mid = (l + u) / 2;
		bool val = isValid(mid);

		if (val)
		{
			u = mid;
		}
		else
		{
			l = mid;
		}
	}

	if (isValid(u))
	{
		return u;
	}
	else
	{
		return l;
	}

}

int main()
{
	while (cin >> N >> B)
	{
		if ((N == -1) && (B == -1)) break;

		for (long i = 0; i < N; ++i)
		{
			cin >> cities[i];
		}

		cout << getMaxPeoplePerBallot() << endl;
	}

	return 0;
}