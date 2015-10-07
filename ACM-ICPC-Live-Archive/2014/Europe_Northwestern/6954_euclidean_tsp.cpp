#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int n;
	double p, s, v;

	// Precision asked by the statement
	cout.setf(ios::fixed);
	cout.precision(10);

	while (cin >> n >> p >> s >> v)
	{
		// Common used values already computed so as not to 
		// recompute them several times
		long double a = s / v;
		long double b = double(n) / (p * 1000000000.0);
		long double e = log2(n);
		long double c = log(e);
		long double d = sqrt(2);
		long double tolerance = 1E-6;

		long double c0 = 1.0;
		long double c1 = 1.0;

		bool solutionFound = false;

		// Newton's method (https://en.wikipedia.org/wiki/Newton%27s_method)
		// The idea is to find the value of 'c' that makes the first derivative = 0,
		// that is, the function f(x) reaches the minimum amount of time. Therefore,
		// we must also use the second derivative to find the value of 'c' using the
		// Newton's method.
		// The function f(x) is the sum of the running time of the algorithm and the
		// seconds needed by Miroslava.
		while (true)
		{
			// Formula of the first derivative f'x()
			long double y = -a / (c0 * c0) + b * d * c * pow(e, c0 * d);
			
			// Formula of the second derivative f''(x)
			long double yprime = 2.0 * a / (c0 * c0 * c0) + 2 * b * c * c * pow(e, c0 * d);

			c1 = c0 - y / yprime;

			if ((fabs(c1 - c0) / fabs(c1)) < tolerance)
			{
				solutionFound = true;
				break;
			}

			c0 = c1;
		}

		// Compute the value of the original function
		long double fx = a + a / c1 + b * pow(e, c1 * d);

		// Output the time value and the c value
		cout << fx << " " << c1 << endl;
	}

	return 0;
}

