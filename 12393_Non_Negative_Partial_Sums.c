#include <stdio.h>

int vals[1000000];
long sums[1000000];
long rec;
int nvals;

static int
solve(void)
{
	int i, total;

	if(rec>=0) 
		total = 1;
	else
		total = 0;
	for(i=nvals-1; i>0; i--) {
		if(vals[i] > 0)
			rec += vals[i];
		if(rec >= 0)
			total++;
	}
	return total;
}

int
main()
{
	int i;
	long sum;

	for(;;) {
		scanf("%d", &nvals);
		if(nvals==0)
			break;
		rec = sum = 0;
		for(i=0; i<nvals; i++) {
			scanf("%d", &vals[i]);
			sum += vals[i];
			sums[i] = sum;
			if(sum<rec)
				rec = sum;
		}
		printf("%d\n", solve());
	}
	return 0;
}
