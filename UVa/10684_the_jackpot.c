#include <stdio.h>

int main()
{
	int N, n, max, cons_max;
	while(scanf("%d", &N) && N) {
		max = cons_max = 0;
		while(N--) {
			scanf("%d", &n);
			cons_max = cons_max + n;
			if(n > cons_max)
				cons_max = n;
			if(cons_max > max)
				max = cons_max;
		}
		if(!max)
			puts("Losing streak.");
		else
			printf("The maximum winning streak is %d.\n", max);
	}
	return 0;
}
