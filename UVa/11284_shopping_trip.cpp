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

typedef int Subset;
typedef int Cost;

Cost price_save[OPERAS], distances[OPERAS][OPERAS], adj_mat[STORES][STORES],
	tsp_memoize[1 << (OPERAS+1)][OPERAS];
int stores[OPERAS];
int n_operas;
Cost total_minimum;

constexpr Cost sentinel = numeric_limits<int>::max();

#define TSP(subset, i) (tsp_memoize[subset][i] == sentinel ? tsp(subset, i) : tsp_memoize[subset][i])

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
	minimum -= price_save[i];
	int m = minimum + adj_mat[0][stores[i]];
	if(m < total_minimum)
		total_minimum = m;
#ifndef ONLINE_JUDGE
	printf("tsp_memoize[%x][%d] = %d, %d\n", subset, i, minimum, minimum + adj_mat[0][stores[i]]);
#endif
	return tsp_memoize[subset][i] = minimum;
}

int main() {
	int N_cases;
	scanf("%d", &N_cases);
	while(N_cases--) {
		int n_stores, n_roads;
		scanf("%d %d", &n_stores, &n_roads);
		n_stores++; // count the house
		std::fill(&adj_mat[0][0], &adj_mat[0][0]+sizeof(adj_mat)/sizeof(adj_mat[0][0]), sentinel);
		while(n_roads--) {
			int i, j;
			scanf("%d %d", &i, &j);
			Cost dollars, cents;
			scanf("%d.%d", &dollars, &cents);
			dollars = dollars * 100 + cents;
			if(dollars < adj_mat[j][i])
				adj_mat[j][i] = adj_mat[i][j] = dollars;
		}

		for (int k = 0; k < n_stores; k++)
			for (int i = 0; i < n_stores; i++)
				for (int j = 0; j < n_stores; j++) {
					if(adj_mat[i][k] == sentinel || adj_mat[k][j] == sentinel)
						continue;
					adj_mat[i][j] = std::min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);
				}

		scanf("%d", &n_operas);
		for(int i=0; i<n_operas; i++) {
			scanf("%d", &stores[i]);
			Cost dollars, cents;
			scanf("%d.%d", &dollars, &cents);
			price_save[i] = dollars*100 + cents;
		}
		for(int i=0; i<n_operas; i++)
			for(int j=0; j<n_operas; j++)
				distances[i][j] = adj_mat[stores[i]][stores[j]];

#ifndef ONLINE_JUDGE
		for(int i=0; i<n_stores; i++) {
			for(int j=0; j<n_stores; j++)
				printf("%d ", adj_mat[i][j]);
			putchar('\n');
		}

		for(int i=0; i<n_operas; i++) {
			for(int j=0; j<n_operas; j++)
				printf("%d ", distances[i][j]);
			putchar('\n');
		}

		puts("distances from 0:");
		for(int i=0; i<n_operas; i++)
			printf("%d ", adj_mat[0][stores[i]]);
		putchar('\n');
		puts("saving costs");
		for(int i=0; i<n_operas; i++)
			printf("%d ", price_save[i]);
		putchar('\n');
#endif

		total_minimum = numeric_limits<Cost>::max();
		fill(&tsp_memoize[0][0], &tsp_memoize[0][0] + sizeof(tsp_memoize) / sizeof(tsp_memoize[0][0]), sentinel);
		for(int i=0; i<n_operas; i++) {
			int v = adj_mat[0][stores[i]];
			if(v == sentinel) continue;
			v = tsp_memoize[1<<i][i] = v - price_save[i];
#ifndef ONLINE_JUDGE
			printf("tsp_memoize[%x][%d] = %d\n", 1<<i, i, tsp_memoize[1<<i][i]);
#endif
			v += adj_mat[0][stores[i]];
			if(v < total_minimum)
				total_minimum = v;
		}
		if(n_operas > 1)
			for(int i=0; i<n_operas; i++)
				tsp(0xffff >> (16 - n_operas), i);

		if(total_minimum >= 0)
			puts("Don't leave the house");
		else
			printf("Daniel can save $%d.%02d\n", (-total_minimum) / 100, (-total_minimum) % 100);
	}
	return 0;
}
