/* algorithm from: http://www.algorithmist.com/index.php/Longest_Increasing_Subsequence */
#include <stdio.h>
#include <string.h>

#define MAX 1000000

int seq[MAX], predecessor[MAX], seq_sz;
int ind[MAX], ind_sz;

int main() {
	seq_sz = ind_sz = 0;
	if(scanf("%d", &seq[seq_sz++])) {
		ind[0] = 0;
		ind_sz = 1;
		while(scanf("%d", &seq[seq_sz++]) == 1) {
			/*  If next element a[i] is greater than last element of */
			/*  current longest subsequence a[b.back()], just push it at back of "b" and continue */
			int i = seq_sz-1;
			if (seq[ind[ind_sz-1]] < seq[i]) 
			{
				predecessor[i] = ind[ind_sz-1];
				ind[ind_sz++] = i;
				continue;
			}

			/*  Binary search to find the smallest element referenced by b which is just bigger than a[i] */
			/*  Note : Binary search is performed on b (and not a). */
			/*  Size of b is always <=k and hence contributes O(log k) to complexity.     */
			int u = 0, v = ind_sz-1;
			while(u < v) {
				int c = (u + v) / 2;
				if (seq[ind[c]] < seq[i])
					u = c+1;
				else
					v = c;
			}

			/*  Update b if new value is smaller then previously referenced value  */
			if (seq[i] < seq[ind[u]]) 
			{
				if (u > 0)
					predecessor[i] = ind[u-1];
				ind[u] = i;
			}	
		}
	}

	printf("%d\n-\n", ind_sz);
	int i = ind[ind_sz-1], j;
	for(j=0; j<ind_sz; j++, i = predecessor[i])
		ind[j] = seq[i];
	while(ind_sz--)
		printf("%d\n", ind[ind_sz]);
	return 0;
}
