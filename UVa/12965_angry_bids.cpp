#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> P;

int main() {
	int Ncases;
	cin >> Ncases;
	while(Ncases--) {
		P w;
		vector<P> all;
		int p, c;
		cin >> p >> c;
		w.second = 1;
		for(int i=0; i<p; i++) {
			cin >> w.first;
			all.push_back(w);
		}
		w.second = -1;
		for(int i=0; i<c; i++) {
			cin >> w.first;
			w.first++;
			all.push_back(w);
		}
		sort(all.begin(), all.end());
		int sz = all.size();
		int price, max_sum, sum, angry;
		max_sum = 0;
		sum = 0;
		int anp = p, anc = 0;
		price = 0;
		angry = anp;
		for(int i=0; i<sz; i++) {
			sum += all[i].second;
			if(all[i].second == 1)
				anp--;
			else
				anc++;
			if(sum > max_sum) {
				max_sum = sum;
				angry = anp + anc;
				price = all[i].first;
			}
		}
		cout << price << " " << angry << endl;
	}
	return 0;
}
