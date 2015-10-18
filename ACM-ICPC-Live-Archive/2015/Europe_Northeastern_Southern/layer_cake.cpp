#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <utility>

#define PB push_back

using namespace std;

typedef long long LI;

int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		map<int, vector<int> > layer_other_side;
		unordered_map<int, int> num_layers;
		for(int i=0; i<n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			if(layer_other_side.find(a) == layer_other_side.end())
				layer_other_side[a] = vector<int>();
			if(layer_other_side.find(b) == layer_other_side.end())
				layer_other_side[b] = vector<int>();
			layer_other_side[a].PB(b);
			if(a != b)
				layer_other_side[b].PB(a);
			num_layers[a] = 0;
			num_layers[b] = 0;
		}

		LI max_volume = 0;
		int max_w, max_h;
		// iterate starting from the biggest size, so we can look at the
		// _current_ size instead of the previous one, and also we can prune
		auto los_rend = layer_other_side.rend();
		auto los_rbegin = layer_other_side.rbegin();
		for(auto it=los_rbegin; it != los_rend; it++) {
			auto v_end = it->second.end();
			for(auto l = it->second.begin(); l != v_end; l++) {
				if(it->first < *l)
					num_layers[it->first]--;
				num_layers[*l]++;
			}
			int layers = 0;
			for(auto jt=los_rbegin; jt != los_rend; jt++) {
				int w = it->first, h = jt->first;
				layers += num_layers[h];
				LI volume = ((LI)w) * ((LI)h);
				LI max_possible_volume = ((LI)n) * volume;
				if(max_possible_volume < max_volume)
					break;
				volume *= (LI)layers;
				if(volume > max_volume) {
					max_volume = volume;
					max_w = w;
					max_h = h;
				}
			}
		}
		cout << max_volume << endl;
		cout << max_w << ' ' << max_h << endl;
	}
	return 0;
}
