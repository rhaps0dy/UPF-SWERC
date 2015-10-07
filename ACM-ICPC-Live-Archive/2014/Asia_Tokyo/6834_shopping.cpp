#include <cstdio>
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int N, m;
	vector<pair<int, int> > intervals;
	while(cin >> N >> m) {
		intervals.clear();
		while(m--) {
			int a, b;
			scanf("%d %d", &b, &a);
			intervals.push_back(make_pair(b, 1));
			intervals.push_back(make_pair(a, -1));
		}

		sort(intervals.begin(), intervals.end());

		int sum = 0, prev_sum = 0;
		int begin_interval = 0;
		int sz = intervals.size();
		int walk = N + 1;
		for(int i=0; i<sz; i++, prev_sum = sum) {
			sum += intervals[i].second;
			if(prev_sum == 0 && sum > 0)
				begin_interval = intervals[i].first;
			else if(prev_sum > 0 && sum == 0) {
				walk += (intervals[i].first - begin_interval) * 2;
			}
		}
		printf("%d\n", walk);
	}
	return 0;
}
