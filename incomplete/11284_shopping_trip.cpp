#include <cstdio>
#include <algorithm>
#include <limits>
#include <cstring>
#include <cstdint>
#include <map>
// both include the house
#define OPERAS 13
#define STORES 51

int price_save[OPERAS];
int stores[OPERAS];
int distances[OPERAS][OPERAS];
int adj_mat[STORES][STORES];

static int subset[OPERAS+1]; // k <= N
void init_subset(int k, int n) {
	int i;
	for(i=0; i<k; i++)
		subset[i] = i;
	subset[k] = n;
}
bool next_subset(int k, int n) {
	int i;

	for(i=1; i<k; i++) {
		if(subset[k-i] == n-i) {
			val prev = subset[k-i-i] + 2;
			if(prev < subset[k-i+1]-1)
				subset[k-1] = prev;
		} else {
			subset[k-1]++;
			return true;
		}
	}
	if(++subset[0] <= n-k) {
		for(i=1; i<k; i++)
			subset[i] = i+subset[0];
		return true;
	}
	return false;
}
typedef SubsetHash uint64_t;
SubsetHash subset_hash(int k) {
	SubsetHash res = subset[0];
	for(int i=1; i<k; i++)
		// assume n < 16;
		res |= (subset[i] & 0xf) << (4*i); 
	return res;
}

int main() {
	int N_cases;
	scanf("%d", &N_cases);
	while(N_cases--) {
		int n_stores, n_roads;
		scanf("%d %d", &n_stores, &n_roads);
		std::fill(distances, distances+OPERAS*OPERAS, std::infinity());
		std::fill(adj_mat, adj_mat+STORES*STORES, std::infinity());
		while(n_roads--) {
			int i, j;
			scanf("%d %d", &i, &j);
			int dollars, cents;
			scanf("%d.%d", &dollars, &cents);
			distances[j][i] = distances[i][j] = dollars*100 + cents;
		}
		int n_operas;
		scanf("%d", &n_operas);
		for(int i=0; i<n_operas; i++) {
			scanf("%d", &stores[i+1]);
			int dollars, cents;
			scanf("%d.%d", &dollars, &cents);
			price_save[i] = dollars*100 + cents;
		}

		for (int k = 0; k < n_stores; k++)
			for (int i = 0; i < n_stores; i++)
				for (int j = 0; j < n_stores; j++)
					adj_mat[i][j] = std::min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);

		for(int i=0; i<n_operas; i++)
			for(int j=0; j<n_operas; j++)
				distances[i][j] = adj_mat[stores[i]][stores[j]];

		std::map<SubsetHash, int>
		

		
	}
	return 0;
}
