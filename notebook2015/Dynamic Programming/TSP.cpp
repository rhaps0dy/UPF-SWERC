// TSP in O(n^2 * 2^n). Subset is bitmask, Cost is cost.
// tsp_memoize[subset][j] stores the shortest path starting at node -1,
// including the nodes in the subset and finishing at node j.
// This is for the TSP with N+1 nodes. We pick the first one arbitrarily.
Cost distances[N][N], tsp_memoize[1 << (N+1)][N];
const Cost sentinel=-0x3f3f3f3f;
#define TSP(subset, i) (tsp_memoize[subset][i] == sentinel ? \
						tsp(subset, i) : tsp_memoize[subset][i])

Cost tsp(const Subset subset, const int i) {
	Subset without = subset ^ (1 << i);
	Cost minimum = numeric_limits<Cost>::max();
	for(int j=0; j<n_nodes; j++) {
		if(j==i || (without & (1 << j)) == 0)
			continue;
		Cost v = TSP(without, j);
		v += distances[i][j];
		if(v < minimum)
			minimum = v;
	}
	return tsp_memoize[subset][i] = minimum;
}

/* fill tsp_memoize with sentinel */
tsp_memoize[1<<i][i] = distance /* from -1 to i */
for(int i=0; i<n_nodes; i++)
	tsp(0xffff >> (16 - n_nodes), i) /* + distance from i to -1 */;
