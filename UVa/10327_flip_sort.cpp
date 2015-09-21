#include <iostream>

using namespace std;

int nums[1001];

int main()
{
	int N = 0;
	
	while (cin >> N)
	{
		for (int i = 0; i < N; ++i)
		{
			cin >> nums[i];
		}
		
		int s = 0;
	
		// Bubble Sort: Since only adjacent numbers can be flipped,
		// it is the algorithm that suits this exercise
		// https://en.wikipedia.org/wiki/Bubble_sort
		for (int i = 1; i < N; ++i)
		{
			for (int j = 0; j < N - i; ++j)
			{
				if (nums[j] > nums[j + 1])
				{
					int t = nums[j];
					nums[j] = nums[j + 1];
					nums[j + 1] = t;
					++s;
				}	
			}
		}
		
		cout << "Minimum exchange operations : " << s << endl;
	}
	
	return 0;
}