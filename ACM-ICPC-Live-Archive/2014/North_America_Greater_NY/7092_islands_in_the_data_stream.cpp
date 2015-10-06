#include <iostream>
#include <set>

using namespace std;

int I[12];

int main()
{
	int P = 0;
	cin >> P;
	
	while (P--)
	{
		int K = 0;
		cin >> K;
		
		set<int> islands;
		int island;
		
		for (int i = 0; i < 12; ++i)
		{
			cin >> island;
			islands.insert(island);
			I[i] = island;
		}
		
		set<int>::iterator it = islands.begin();
		set< pair<int, int> > islandsets;
		
		int numIslands = 0;
		int origin = 0, finale = 0;
		
		
		for ( ; it != islands.end(); ++it)
		{
			int i1 = *it;
			bool islandStarted = false;
			
			for (int i = 0; i < 12; ++i)
			{
				if (I[i] > i1 && !islandStarted)
				{
					islandStarted = true;
					origin = i;
				}
				else if (I[i] <= i1 && islandStarted)
				{
					islandStarted = false;
					finale = i - 1;
					islandsets.insert(make_pair(origin, finale));
					++numIslands;
				}
			}
		}
		
		cout << K << " " << islandsets.size() << endl;
	}
	
	return 0;
}