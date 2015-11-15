/**
 * Problem 11172
 * DanielFB93
 * 12/04/2014
 */

#include <iostream>

int main()
{
	unsigned int nPairs = 0;
	int n1 = 0;
	int n2 = 0;

	std::cin >> nPairs;

	for (unsigned int i = 0; i < nPairs; ++i)
	{
		std::cin >> n1;
		std::cin >> n2;

		if (n1 > n2)
		{
			std::cout << ">" << std::endl;
		}
		else if (n1 < n2)
		{
			std::cout << "<" << std::endl;
		}
		else
		{
			std::cout << "=" << std::endl;
		}
	}

	return 0;
}