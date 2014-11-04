#include <stdio.h>
#include <stdlib.h>

#define MAX_N (100*100)

enum robot {
	NONE,
	VERT,
	HOR
};

typedef struct {
	int x, y, is_obstacle;
	enum robot robot;
} Point;

Point *vertorder[MAX_N], *hororder[MAX_N];
Point points[MAX_N];
int npoints;

static int
compar_vert(const void *_a, const void *_b)
{
	Point *a, *b;

	a = *(Point **)_a;
	b = *(Point **)_b;

	if(a->x < b->x) return -1;
	if(a->x > b->x) return 1;
	if(a->y < b->y) return -1;
	return 1;
}

static int
compar_hor(const void *_a, const void *_b)
{
	Point *a, *b;

	a = *(Point **)_a;
	b = *(Point **)_b;

	if(a->y < b->y) return -1;
	if(a->y > b->y) return 1;
	if(a->x < b->x) return -1;
	return 1;
}

static void
doit(void)
{
	int i, j, nrobots, nlines;
	Point **p;

	/* width, height */
	scanf("%*d %*d");
	/* points of interest */
	scanf("%d", &npoints);
	for(i=0; i<npoints; i++) {
		scanf("%d %d", &points[i].y, &points[i].x);
		points[i].is_obstacle = 0;
		points[i].robot = NONE;
		vertorder[i] = hororder[i] = &points[i];
	}

	/* obstacles */
	scanf("%d", &i);
	npoints += i;
	for(; i<npoints; i++) {
		scanf("%d %d", &points[i].y, &points[i].x);
		points[i].is_obstacle = 1;
		points[i].robot = NONE;
		vertorder[i] = hororder[i] = &points[i];
	}

	qsort(vertorder, npoints, sizeof(Point *), compar_vert);
	qsort(hororder, npoints, sizeof(Point *), compar_hor);

	puts("Horizontal order:");
	for(i=0; i<npoints; i++)
		printf("(%d %d %d) ", hororder[i]->x, hororder[i]->y, hororder[i]->is_obstacle);
	putchar('\n');

	puts("Vertical order:");
	for(i=0; i<npoints; i++)
		printf("(%d %d %d) ", vertorder[i]->x, vertorder[i]->y, vertorder[i]->is_obstacle);
	putchar('\n');

	nrobots = 0;
	if(!hororder[0]->is_obstacle) {
		hororder[0]->robot = HOR;
		nrobots++;
	}
	for(i=1; i<npoints; i++) {
		if(hororder[i-1]->is_obstacle) {
			hororder[i]->robot = HOR;
			nrobots++;
		}
	}

	if(!vertorder[0]->is_obstacle) {
		if(vertorder[0]->robot == NONE) {
			/* if putting a vertical line here eliminates one or more horizontal
			 * lines, do it */
			nlines = 0;
			for(j=0; !vertorder[j].is_obstacle && j<npoints; j++) {
				p = (Point **) bsearch(vertorder[j], hororder, sizeof(Point *), npoints, hor_compar)
				/* TOCONTIUE */
			}
		} else {
		}
	}
}

int
main()
{
	doit();
	return 0;
}
