#include <stdio.h>
#include <string.h>

#define MAX 100

typedef long long LI;

LI mat[MAX][MAX];

int main() {
	int i, j, k, l, N, M;
	LI area, money, K;
	int n_case, n_cases;
	scanf("%d", &n_cases);
	for(n_case = 1; n_case <= n_cases; n_case++) {
		scanf("%d %d %lld", &N, &M, &K);
		for(i=0; i<N; i++) {
			scanf("%lld", &mat[i][0]);
			for(j=1; j<M; j++) {
				scanf("%lld", &mat[i][j]);
				mat[i][j] += mat[i][j-1];
			}
		}
		for(i=1; i<N; i++)
			for(j=0; j<M; j++)
				mat[i][j] += mat[i-1][j];

		money = 0;
		area = 0;
		for(i=0; i<N; i++) {
			if((N-i) * M < area)
				break;
			for(j=0; j<M; j++) {
				if((N-i) * (M-j) < area)
					break;
				for(k=i; k<N; k++) {
					for(l=j; l<M; l++) {
						int new_area = (k-i+1)*(l-j+1);
						if(new_area < area)
							continue;
						LI new_money = mat[k][l];
						if(i != 0) {
							if(j != 0)
								new_money += mat[i-1][j-1];
							new_money -= mat[i-1][l];
						}
						if(j != 0)
							new_money -= mat[k][j-1];
						if(new_money > K)
							continue;
						if(new_area == area && new_money < money)
							money = new_money;
						else if(new_area > area) {
							area = new_area;
							money = new_money;
						}
					}
				}
			}
		}
		printf("Case #%d: %lld %lld\n", n_case, area, money);
	}
	return 0;
}
