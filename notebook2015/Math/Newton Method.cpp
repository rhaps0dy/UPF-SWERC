long double tolerance = 1E-6;
long double c0 = 1.0;
long double c1 = 1.0;
bool solutionFound = false;

// find the value of 'c' that makes the function equal to = 0
// might also be used in optimization problems setting y as
// the first derivative and yprime as the second
while (true)
{
	long double y = /* formula of the original function */;
	long double yprime = /* formula of the first derivative respect to c */;
	c1 = c0 - y / yprime;
	if ((fabs(c1 - c0) / fabs(c1)) < tolerance)
	{
		solutionFound = true;
		break;
	}
	c0 = c1;
}

