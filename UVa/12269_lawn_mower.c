#include <stdio.h>
#include <stdlib.h>

#define LENGTH 100.L
#define WIDTH   75.L

double positions[1000], mowidth;

static int
is_all_mowed(int n, double maxlen)
{
	int i;

	if(maxlen == 0)
		return 0;

	if(positions[0] > mowidth)
		return 0;

	for(i=1; i<n; i++) {
		if(positions[i] - mowidth > positions[i-1] + mowidth)
			return 0;
	}

	if(maxlen - mowidth > positions[n-1])
		return 0;
	return 1;
}

static int
double_order(const void *_a, const void *_b)
{
	double a, b;

	a = *(double *)_a;
	b = *(double *)_b;
	if(a == b) return 0;
	if(a < b) return -1;
	return 1;
}

static void
get_mows(int n)
{
	int i;
	for(i=0; i<n; i++)
		scanf("%lf", &positions[i]);
	qsort(positions, n, sizeof(double), double_order);
}

int
main()
{
	int nx, ny, cache;

	for(;;) {
		scanf("%d %d %lf", &nx, &ny, &mowidth);
		mowidth /= 2.L;
		if(nx == 0 && ny == 0 && mowidth == 0.L)
			return 0;
		get_mows(nx);
		cache = is_all_mowed(nx, WIDTH);
		get_mows(ny);
		if(cache && is_all_mowed(ny, LENGTH))
			puts("YES");
		else puts("NO");
	}
	return 0;
}
