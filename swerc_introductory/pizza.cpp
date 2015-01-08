#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

int ltime[3001][3001], rtime[3001][3001];
int N, LN, RN, lefts[3001], rights[3001];

int
calc_by_dp()
{
	int i, j, a, b, dist;

	memset(dp, 0, sizeof(dp));

	dp[0][1].cost = rights[0]*N;
	dp[1][0].cost = abs(lefts[LN-1]*N);
	dp[1][0].is_l = 1;

	for(i=2; i<=RN; i++)
		dp[0][i].cost = dp[0][i-1].cost + (rights[i-1]-rights[i-2])*(N-i+1);

	for(j=2; j<=LN; j++) {
		dp[j][0].cost = dp[j-1][0].cost + abs(lefts[LN-(j-1)-1]-lefts[LN-(j-2)-1])*(N-j+1);
		dp[j][0].is_l = 1;
	}

	for(j=1; j<=LN; j++) {
		for(i=1; i<=RN; i++) {
			dist = lefts[LN-j];
#ifdef DEBUG
			printf("%d ", dist);
#endif
			if(dp[j-1][i].is_l) {
				dist -= lefts[LN-(j-1)];
#ifdef DEBUG
				printf("(is_l) %d -- ", lefts[LN-(j-1)]);
#endif
			} else {
				dist -= rights[i-1];
#ifdef DEBUG
				printf("%d -- ", rights[i-1]);
#endif
			}
			a = dp[j-1][i].cost + abs(dist)*(N-i-j+1);

			dist = rights[i-1];
#ifdef DEBUG
			printf("%d ", dist);
#endif
			if(dp[j][i-1].is_l) {
				dist -= lefts[LN-j];
#ifdef DEBUG
				printf("(is_l) %d\n", lefts[LN-j]);
#endif
			} else {
				dist -= rights[i-1-1];
#ifdef DEBUG
				printf("%d\n", rights[i-1-1]);
#endif
			}
			b = dp[j][i-1].cost + abs(dist)*(N-i-j+1);
			if(a < b) {
				dp[j][i].cost = a;
				dp[j][i].is_l = 1;
			} else {
				dp[j][i].cost = b;
			}
		}
	}
#ifdef DEBUG
	for(j=0; j<=LN; j++) {
		for(i=0; i<=RN; i++)
			printf("%d-%d ", dp[j][i].cost, dp[j][i].is_l);
		putchar('\n');
	}
#endif
	return dp[LN][RN].cost;
}

int houses[3000];

int
calc_by_brute()
{
	int i, j, rec, cur, time;

	houses[0] = 0;
	for(i=1; i<=LN; i++)
		houses[i] = lefts[i-1];
	for(j=0; j<RN; j++, i++)
		houses[i] = rights[j];
	rec = 1000000000;
	do {
		cur = 0;
		time = 0;
		for(i=1; i<=N; i++) {
			time += abs(houses[i]-houses[i-1]);
			cur += time;
		}
		if(cur < rec) rec = cur;
	} while(next_permutation(houses+1, houses+N+1));
	return rec;
}

/*
int
main()
{
	int i, j;

	scanf("%d", &N);

	for(i=0; i<N; i++) {
		scanf("%d", &lefts[i]);
		if(lefts[i] > 0) {
			rights[0] = lefts[i];
			LN = i;
			i++;
			break;
		}
	}
	for(j=1; i<N; i++, j++)
		scanf("%d", &rights[j]);
	RN = j;

	printf("%d - ", calc_by_dp());
	printf("%d\n", calc_by_brute());
	return 0;
}*/

#define MAX 10

int used[1000];

int
main()
{
	int i;

	srand(time(NULL));
	N = rand()%MAX;
	RN = rand()%MAX;
	LN = N - RN;
	
	memset(used, 0, sizeof(used));
	for(i=0; i<RN; i++) {
		rights[i] = rand()%1000;
		if(used[rights[i]]) i--;
		else used[rights[i]] = 1;
	}
	memset(used, 0, sizeof(used));
	for(i=0; i<LN; i++) {
		lefts[i] = rand()%1000;
		if(used[lefts[i]]) i--;
		else used[lefts[i]] = 1;
	}
	sort(lefts, lefts+LN);
	sort(rights, rights+RN);
	printf("%d - ", calc_by_dp());
	printf("%d\n", calc_by_brute());
	return 0;
}
