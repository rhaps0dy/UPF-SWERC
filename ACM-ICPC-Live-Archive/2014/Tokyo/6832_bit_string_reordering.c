#include <stdio.h>
#include <string.h>

#define MAX 15

int solve(const int const_bits[MAX], const int target[MAX], const int N) {
	int i, j;
	int swaps = 0;
	static int bits[MAX];
	memcpy(bits, const_bits, sizeof(bits));
	for(i=0; i<N; i++) {
		if(bits[i] != target[i]) {
			for(j=i+1; target[i] != bits[j]; j++);
			bits[j] = bits[i];
/*			bits[i] = target[i]; not needed for answer */
			swaps += j - i;
		}
	}
	return swaps;
}

int main() {
	int N, M, i, j, k;
	int bits[MAX], run_length[MAX], target[MAX];
	int odd_rl, even_rl, num_ones;
	while(scanf("%d %d", &N, &M) == 2) {
		num_ones = 0;
		for(i=0; i<N; i++) {
			scanf("%d", bits+i);
			if(bits[i])
				num_ones++;
		}
		odd_rl = even_rl = 0;
		for(i=0; i<M; i++) {
			scanf("%d", run_length+i);
			if(i%2)
				odd_rl += run_length[i];
			else
				even_rl += run_length[i];
		}

		int min_swaps = 9999999, swaps;

		if(odd_rl == num_ones) {
			for(k=i=0; i<M; i++)
				for(j=0; j<run_length[i]; j++)
					target[k++] = i % 2;
			swaps = solve(bits, target, N);
			if(swaps < min_swaps)
				min_swaps = swaps;
		}
		if(even_rl == num_ones) {
			for(k=i=0; i<M; i++)
				for(j=0; j<run_length[i]; j++)
					target[k++] = (i+1) % 2;
			swaps = solve(bits, target, N);
			if(swaps < min_swaps)
				min_swaps = swaps;
		}

		printf("%d\n", min_swaps);
	}
	return 0;
}
