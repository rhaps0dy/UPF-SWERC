// TSP in O(n^2 * 2^n). Subset is bitmask, Cost is cost.
// tsp_memoize[subset][i] stores the shortest tsp of the subset starting at i.
// If you have a starting node, it 's not included in the search .you add the distance to it at the beginning
Cost distances[N][N], tsp_memoize[1 << (N+1)][N];
const sentinel=-0x3f3f3f3f;
#define TSP(subset, i) (tsp_memoize[subset][i] == sentinel ? \
						tsp(subset, i) : tsp_memoize[subset][i])

Cost tsp(const Subset subset, const int i) {
	Subset without = subset ^ (1 << i);
	Cost minimum = numeric_limits<Cost>::max();
	for(int j=0; j<n_operas; j++) {
		if(j==i || (without & (1 << j)) == 0)
			continue;
		Cost v = TSP(without, j);
		v += distances[i][j];
		if(v < minimum)
			minimum = v;
	}
	return tsp_memoize[subset][i] = minimum;
}

tsp_memoize[1<<i][i] = v - price_save[i];
for(int i=0; i<n_operas; i++)
	tsp(0xffff >> (16 - n_operas), i);
