#include<bits/stdc++.h>

using namespace std;

int x[100000];

int main() {
	int N;
	cin >> N;
	for(int i=0; i<N; i++) {
		cin >> x[i];
	}
	int max_len = 1;
	int mx, mn, mx_i, mn_i;
	mx = mn = x[0];
	mx_i = mn_i = 0;
	int j=0;
	for(int i=1; i<N; i++) {
		if(x[i] >= mx) {
			if(abs(x[i] - mn) > 1) {
				if(abs(x[i] - mx) > 1) {
					j = mx_i = mn_i = i;
					mx = mn = x[i];
				} else {
					if(mx_i >= mn_i) {
						j = mn_i + 1;
						mn_i = mx_i;
						assert(mx == x[j]);
						mn = mx;
						mx = x[i];
						mx_i = i;
					} else {
						j = mx_i = mn_i = i;
						mx = mn = x[i];
					}
				}
			} else {
				mx = x[i];
				mx_i = i;
			}
		}
		if(x[i] <= mn) {
			if(abs(mx - x[i]) > 1) {
				if(abs(x[i] - mn) > 1) {
					j = mx_i = mn_i = i;
					mx = mn = x[i];
				} else {
					if(mn_i >= mx_i) {
						j = mx_i + 1;
						mx_i = mn_i;
						assert(mn == x[j]);
						mx = mn;
						mn = x[i];
						mn_i = i;
					} else {
						j = mx_i = mn_i = i;
						mx = mn = x[i];
					}
				}
			} else {
				mn = x[i];
				mn_i = i;
			}
		}
//		cout << mx << ' ' << mn << ' ' << mx_i << ' ' << mn_i << ' ' << x[i] << endl;
		max_len = max(max_len, i-j+1);
	}
	cout << max_len << endl;
	return 0;
}
