#include <stdio.h>
#include <math.h>
#include <float.h>

// Number of houses
unsigned N = 0;

// Coordinates of each house
double HX[50001];
double HY[50001];

// Left and right bounds in ternary search
double L = 0.0;
double R = 0.0;

// Epsillon(9 decimals because output has 9, so better approx)
const double E = 0.00000001;

// Return max squared distance to a point at (x,0)
// Error that I did: do the MEAN squared distance -> not correct since we want
// to minimize the distance to the furthest point
double getMaxSquaredDistanceTo(double x)
{
	double max = -DBL_MAX;

	unsigned i;
	for (i = 0; i < N; ++i)
	{
		double diff = HX[i] - x;
		double dist = diff * diff + HY[i] * HY[i];

		if (dist > max)
		{
			max = dist;
		}
	}

	return max;
}

int main()
{
	while (1)
	{
		scanf("%u", &N);

		if (N == 0) break;

		L = 200000;
		R = -200000;

		unsigned i = 0;
		for (i = 0; i < N; ++i)
		{
			scanf("%lf", &HX[i]);
			scanf("%lf", &HY[i]);

			if (HX[i] < L)
			{
				L = HX[i];
			}

			if (HX[i] > R)
			{
				R = HX[i];
			}
		}

		// Ternary search
		while (1)
		{
			double dist = R - L;

			if (fabs(dist) < E)
				break;

			double leftThird = L + dist / 3;
			double rightThird = R - dist / 3;

			if (getMaxSquaredDistanceTo(leftThird) < getMaxSquaredDistanceTo(rightThird))
			{
				R = rightThird;
			}
			else
			{
				L = leftThird;
			}
		}

		double max = getMaxSquaredDistanceTo(R);
		printf("%.9lf %.9lf\n", R, sqrt(max)); // Note precission and sqrt
	}

	return 0;
}
