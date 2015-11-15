#include <iostream>

using namespace std;

int f(int x)
{
	if (x == 1) return 1;

	int seq = 0;

	if (x % 2) // odd
	{
		seq += 1 + f(3*x+1);
	}
	else
	{
		seq += 1 + f(x/2);
	}

	return seq;
}

int main()
{
	int a, b;

	while (cin >> a >> b)
	{
		int max = -1;

		cout << a << " " << b << " ";

		if (b < a) // swap
		{
			int d = b;
			b = a;
			a = d;
		}

		for (int i = a; i <= b; ++i)
		{
			int c = f(i);
			if (c > max) max = c;
		}

		cout << max << endl;
	}

	return 0;
}
