#include <stdio.h>
#include <stdlib.h>

typedef struct Point Point;
struct Point {
	double x, y;
} start, vec;

typedef struct Gate Gate;
struct Gate {
	double x1, x2, y;
} slalom[1000];

double xs[1000];

int N;

static double
calc_x_at(double y)
{
	/* start.x + vec.x*n = x
	 * start.y + vec.y*n = y */
	double n;

	if(vec.x == 0.0)
		return start.x;
	n = (y-start.y)/vec.y;
	return start.x + vec.x * n;
}

static double
calc_distance(void)
{
	int i, j;
	double x, dist = 0.0;

	vec.x = 0.0;
	vec.y = -1.0;

	for(i=0; i<N; i++) {
		x = xs[i] = calc_x_at(slalom[i].y);
		if(x > slalom[i].x1) {
			if(x < slalom[i].x2) {
				continue;
			} else {
			}
		} else {
		}
	}
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
