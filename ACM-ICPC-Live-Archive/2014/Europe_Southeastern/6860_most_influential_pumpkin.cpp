#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

#define X first
#define Y second
#define MP make_pair
#define PB push_back

// end_i isn't part of the block
struct {
	int n, start_i, med_i, end_i;
} blocks[300];

pair<int, int> pumpkins[60060], pmp_throwaway[60060];

vector<pair<int, int> > increased, non_increased;

static int
smaller_in_block(int i, int median) {
	int min_i, max_i, med_i = blocks[i].med_i, end_i = blocks[i].end_i, start_i = blocks[i].start_i;
	median -= blocks[i].n;
	if(med_i == end_i) {
		if(pumpkins[med_i-1].X < median) {
			return med_i - start_i;
		} else {
			min_i = start_i;
			max_i = end_i;
		}
	} else {
		if(pumpkins[med_i].X < median) {
			min_i = med_i;
			max_i = end_i;
		} else if(med_i == start_i) {
			return 0;
		} else {
			if(pumpkins[med_i-1].X < median) {
				return med_i - start_i;
			} else {
				min_i = start_i;
				max_i = med_i;
			}
		}
	}
	blocks[i].med_i = lower_bound(pumpkins+min_i, pumpkins+max_i, MP(median, -1)) - pumpkins;
	return blocks[i].med_i - start_i;
}

static void
merge_block(int lo, int block_sz, bool increase_over) {
	increased.clear();
	non_increased.clear();
	int block_i = lo/block_sz;
	for(int i=blocks[block_i].start_i; i<blocks[block_i].end_i; i++) {
		if(pumpkins[i].Y >= lo) {
			if(increase_over)
				pumpkins[i].X++;
			increased.PB(pumpkins[i]);
		} else {
			if(!increase_over)
				pumpkins[i].X++;
			non_increased.PB(pumpkins[i]);
		}
	}
	int j=0, k=0, l=blocks[block_i].start_i;
	while(j<increased.size() && k<non_increased.size())
		pumpkins[l++] = (increased[j].X < non_increased[k].X ? increased[j++] : non_increased[k++]);
	while(j<increased.size())
		pumpkins[l++] = increased[j++];
	while(k<non_increased.size())
		pumpkins[l++] = non_increased[k++];
}


static void
water_pumpkins(int lo, int hi, int block_sz) {
	if(lo%block_sz != 0)
		merge_block(lo, block_sz, true);
	if((hi+1)%block_sz != 0)
		merge_block(hi+1, block_sz, false);
	for(int i=lo/block_sz + (lo%block_sz == 0 ? 0 : 1); i<((hi+1)%block_sz == 0 ? 1 : 0) + hi/block_sz; i++)
		blocks[i].n++;
}

int main() {
	int N, K;
	increased.reserve(300);
	non_increased.reserve(300);
	while(scanf("%d %d", &N, &K) == 2) {
		if(N==0 && K==0) continue;
		for(int i=0; i<N; i++) {
			scanf("%d", &pumpkins[i].X);
			pumpkins[i].Y = i;
			pmp_throwaway[i] = pumpkins[i];
		}

		// thug life
		sort(pmp_throwaway, pmp_throwaway+N);
		int median = pmp_throwaway[N/2].X;

		int block_sz = (int)floor(sqrt(N)),
			n_blocks = N/block_sz + (N % block_sz == 0 ? 0 : 1);
		for(int i=0; i<n_blocks; i++) {
			blocks[i].n = 0;
			blocks[i].start_i = blocks[i].med_i = i*block_sz;
			blocks[i].end_i = min((i+1)*block_sz, N);
			sort(pumpkins+blocks[i].start_i, pumpkins+blocks[i].end_i);
		}

#ifndef ONLINE_JUDGE
		printf("Median: %d\n", median);
		putchar('|');
		for(int i=0; i<n_blocks; i++) {
			printf(" %d-%d-%d: ", blocks[i].start_i, smaller_in_block(i, median), blocks[i].end_i);
			for(int j=blocks[i].start_i; j<blocks[i].end_i; j++)
				printf("(%d, %d) ", pumpkins[j].X, pumpkins[j].Y);
			putchar('|');
		}
		putchar('\n');
#endif

		while(K--) {
			int range_s, range_e;
			scanf("%d %d", &range_s, &range_e);
			water_pumpkins(range_s-1, range_e-1, block_sz);
			int smlr = 0;
			for(int i=0; i<n_blocks; i++)
				smlr += smaller_in_block(i, median+1);
			if(smlr <= N/2)
				median++;
			printf("%d\n", median);
#ifndef ONLINE_JUDGE
			printf("smlr %d, N %d\n", smlr, N/2);
		printf("Median: %d\n", median);
		putchar('|');
		for(int i=0; i<n_blocks; i++) {
			printf(" %d-%d-%d: ", blocks[i].start_i, smaller_in_block(i, median), blocks[i].end_i);
			for(int j=blocks[i].start_i; j<blocks[i].end_i; j++)
				printf("(%d, %d) ", pumpkins[j].X + blocks[i].n, pumpkins[j].Y);
			putchar('|');
		}
		putchar('\n');
#endif
#ifdef TEST
			for(int i=0; i<N; i++)
				pmp_throwaway[i].X = pumpkins[i].X + blocks[i/block_sz].n;
			sort(pmp_throwaway, pmp_throwaway+N);
			if(median != pmp_throwaway[N/2].X)
				printf("Median %d is bad, should be %d\n", median, pmp_throwaway[N/2].X);
#endif
		}
	}
	return 0;
}
