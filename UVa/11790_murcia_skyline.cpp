#include <cstdio>
#include <vector>

using namespace std;

int main() {
	int n_cases;
	scanf("%d", &n_cases);
	vector<int> heights, widths;
	for(int c=1; c<=n_cases; c++) {
		int N;
		scanf("%d", &N);
		heights.resize(N);
		widths.resize(N);
		for(int i=0; i<N; i++)
			scanf("%d", &heights[i]);
		for(int i=0; i<N; i++)
			scanf("%d", &widths[i]);

		int max_increasing = widths[0];
		int max_decreasing = widths[0];
		vector<int> increasing(widths);
		vector<int> decreasing(widths);
		for(int i=1; i<N; i++) {
			for(int j=i-1; j>=0; j--) {
				if(heights[i] > heights[j]) {
					int val = widths[i] + increasing[j];
					if(val > increasing[i])
						increasing[i] = val;
				} else if(heights[i] < heights[j]) {
					int val = widths[i] + decreasing[j];
					if(val > decreasing[i])
						decreasing[i] = val;
				}
			}
			if(increasing[i] > max_increasing)
				max_increasing = increasing[i];
			if(decreasing[i] > max_decreasing)
				max_decreasing = decreasing[i];
		}

		if(max_increasing < max_decreasing) {
			printf("Case %d. Decreasing (%d). Increasing (%d).\n", c, max_decreasing, max_increasing);
		} else {
			printf("Case %d. Increasing (%d). Decreasing (%d).\n", c, max_increasing, max_decreasing);
		}
	}
	return 0;
}
