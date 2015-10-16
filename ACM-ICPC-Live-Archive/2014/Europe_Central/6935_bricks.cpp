#include <iostream>
#include <utility>

using namespace std;

int N;
pair<long long, char> B[100001];

int main()
{
	int T;
	cin >> T;
	
	while (T--)
	{
		cin >> N;
		
		int n;
		char c;
		
		long long nw = 0, nb = 0;
		
		for (int i = 0; i < N; ++i)
		{
			cin >> n >> c;

			if (c == 'B') nb += n;
			else if (c == 'W') nw += n;
			
			B[i].first = n;
			B[i].second = c;
		}
	
		long long cw = 0, cb = 0;
		int partitions = 0;
		
		if (nb != 0 && nw != 0)
		{
			for (int i = 0; i < N; ++i)
			{
				const pair<long long, char>& pp = B[i];

				int t = -1;
				
				if (pp.second == 'W')
				{
					long long num = nw * cb;
					
					if (num % nb == 0)
					{
						t = num / nb - cw;
					}
					
					cw += pp.first;
				}
				else
				{
					long long num = nb * cw;
					
					if (num % nw == 0)
					{
						t = num / nw - cb;
					}
					
					cb += pp.first;
				}
				
				if (t > 0 && t <= pp.first)
				{
					++partitions;
				}
			}
		}
		else
		{
			partitions = nw + nb;
		}
		
		cout << partitions << "\n";
	}
	
	return 0;
}

