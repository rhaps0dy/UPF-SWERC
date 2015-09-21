#include <iostream>

using namespace std;

int main()
{
	int P, H, O;

	while (cin >> P >> H >> O)
	{
		if (O - P >= H)
		{
			cout << "Props win!\n";
		}
		else
		{
			cout << "Hunters win!\n";
		}
	}
	
	return 0;
}

