#include <stdio.h>
#include <stdlib.h>

typedef struct Point Point;
struct Point {
	double x, y;
} start;

typedef struct Gate Gate;
struct Gate {
	double x1, x2, y;
} slalom[1000];

int N;

static double
calc_distance(void)
{
	int i, j;
	Point vec = {0, -1.0};

	for(i=0; i<N; i++)
}

int
main()
{
	int i;

	for(;;) {
		scanf("%d", &N);
		if(N==0) return 0;

		scanf("%lf %lf", &start.x, &start.y);
		for(i=0; i<N; i++)
			scanf("%lf %lf %lf", &slalom[i].x1, &slalom[i].x2, &slalom[i].x3);
		printf("%lf", calc_distance());
	}
	return 0;
}
