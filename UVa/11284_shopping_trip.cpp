#include <cstdio>
#include <algorithm>
#include <limits>
#include <cstring>

#define OPERAS 12
#define STORES 51

double price_save[OPERAS];
int stores[OPERAS];
double distances[OPERAS][OPERAS];
double adj_mat[STORES][STORES];

static int subset[OPERAS];
int *next_subset(int k, int n) {
	subset[0]++;
	int i=0;
	while(subset[i] == n && i<k) {
		subset[i] = i;
		i++;
		subset[i]++;
	}
	if(i==k)
}

int main() {
	int N_cases;
	scanf("%d", &N_cases);
	while(N_cases--) {
		int n_stores, n_roads;
		scanf("%d %d", &n_stores, &n_roads);
		std::fill(distances, distances+OPERAS*OPERAS, std::infinity())
		while(n_roads--) {
			int i, j;
			scanf("%d %d", &i, &j);
			scanf("%lf", &distances[i][j]);
			distances[j][i] = distances[i][j];
		}
		int n_operas;
		scanf("%d", &n_operas);
		for(int i=0; i<n_operas; i++) {
			scanf("%d", &stores[i]);
			scanf("%lf", &price_save[i]);
		}

		for (int k = 0; k < n_stores; k++)
			for (int i = 0; i < n_stores; i++)
				for (int j = 0; j < n_stores; j++)
					adj_mat[i][j] = std::min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);

		for(int i=0; i<n_operas; i++)
			for(int j=0; j<n_operas; j++)
				distances[i][j] = adj_mat[stores[i]][stores[j]];

		

		
		
	}
	return 0;
}
