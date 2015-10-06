#include <cstdio>
#include <algorithm>
#include <cassert>
#include <limits>
#include <cstring>
#include <map>

using namespace std;

#define OPERAS 12
// includes the house
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
                       int prev = subset[k-i-i] + 2;
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

typedef int SubsetHash;
typedef int Cost;
SubsetHash subset_hash(int k) {
	SubsetHash res = 0;
	for(int i=0; i<k; i++)
		res |= 1 << subset[i]; 
	return res;
}

int main() {
	int N_cases;
	scanf("%d", &N_cases);
	while(N_cases--) {
		int n_stores, n_roads;
		scanf("%d %d", &n_stores, &n_roads);
		n_stores++; // count the house
		std::fill(&distances[0][0], &distances[0][0]+sizeof(distances)/sizeof(distances[0][0]), 99999999);
		std::fill(&adj_mat[0][0], &adj_mat[0][0]+sizeof(adj_mat)/sizeof(adj_mat[0][0]), 99999999);
		while(n_roads--) {
			int i, j;
			scanf("%d %d", &i, &j);
			int dollars, cents;
			scanf("%d.%d", &dollars, &cents);
			adj_mat[j][i] = adj_mat[i][j] = dollars*100 + cents;
		}

		for (int k = 0; k < n_stores; k++)
			for (int i = 0; i < n_stores; i++)
				for (int j = 0; j < n_stores; j++)
					adj_mat[i][j] = std::min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);

		int n_operas;
		scanf("%d", &n_operas);
		for(int i=0; i<n_operas; i++) {
			scanf("%d", &stores[i]);
			int dollars, cents;
			scanf("%d.%d", &dollars, &cents);
			price_save[i] = dollars*100 + cents;
		}

		for(int i=0; i<n_operas; i++)
			for(int j=0; j<n_operas; j++)
				distances[i][j] = adj_mat[stores[i]][stores[j]];

		// now calculate the tsp with dynamic programming
		map<SubsetHash, Cost> cost[OPERAS];
		Cost total_minimum = numeric_limits<Cost>::max();
		for(int i=0; i<n_operas; i++) {
			int v = adj_mat[0][stores[i]];
			cost[i][1<<i] = v - price_save[i];
			int v2 = v * 2;
			if(v2 < total_minimum)
				total_minimum = v2;
		}

		for(int set_size=2; set_size <= n_operas; set_size++) {
			init_subset(set_size, n_operas);
			do {
				SubsetHash h = subset_hash(set_size);
				for(int i=0; i<set_size; i++) {
					int elem_i = subset[i];
					SubsetHash without = h & ~(1 << elem_i); 
					Cost minimum = numeric_limits<Cost>::max();
					for(int j=0; j<set_size; j++) {
						if(j==i)
							continue;
						int elem_j = subset[j];
						Cost v = cost[elem_j][without] + distances[elem_i][elem_j];
						if(v < minimum)
							minimum = v;
					}
					minimum -= price_save[elem_i];
					cost[elem_i][h] = minimum;
					minimum += adj_mat[0][stores[elem_i]];
					if(minimum < total_minimum)
						total_minimum = minimum;
				}
			} while(next_subset(set_size, n_operas));
		}

#ifndef ONLINE_JUDGE
		for(int i=0; i<n_operas; i++) {
			printf("For node %d:\n", i);
			for(auto it=cost[i].begin(); it !=cost[i].end(); it++) {
				printf("%x -> %d\n", it->first, it->second);
			}
			putchar('\n');
		}
#endif

		if(total_minimum >= 0)
			puts("Don't leave the house");
		else
			printf("Daniel can save $%d.%02d\n", (-total_minimum) / 100, (-total_minimum) % 100);
	}
	return 0;
}
