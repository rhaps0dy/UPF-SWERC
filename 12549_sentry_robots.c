#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_W 100
#define MAX_H 100
#define MAX_N (MAX_W*MAX_H)

typedef struct {
	int x, y, is_obstacle;
} Point;

Point *vertorder[MAX_N], *hororder[MAX_N];
Point points[MAX_N];
Point pospoints[MAX_N];
int npoints, npossiblerobots, w, h;
Point verts[MAX_H][MAX_W], hors[MAX_H][MAX_W];
Point verts2[MAX_H][MAX_W], hors2[MAX_H][MAX_W];

#define TRUE_VALUE(p) ( (p).is_obstacle ? hors[(p).y][(p).x].x : verts[(p).y][(p).x].x )

static int
calc_response(void)
{
	int nrobs, i, x, y;

	nrobs = 0;
	for(i=0; i<npossiblerobots; i++) {
		if(TRUE_VALUE(pospoints[i]) <= 0) continue;
		nrobs++;
/*		PRINT_ALL(); */
		if(pospoints[i].is_obstacle) {
			/* horizontal */
			x = pospoints[i].x;
			y = pospoints[i].y;
			hors[y][x].x = 0;
			/* eliminate this line from records */
			for(; x<w && hors[y][x].is_obstacle != 1; x++) {
				if(hors[y][x].is_obstacle == 2)
					verts[verts[y][x].y][x].x--;	
				verts[y][x].is_obstacle = 0;
				hors[y][x].is_obstacle = 0;
			}
		} else {
			x = pospoints[i].x;
			y = pospoints[i].y;
			verts[y][x].x = 0;
			/* eliminate this line from records */
			for(; y<h && verts[y][x].is_obstacle != 1; y++) {
				if(verts[y][x].is_obstacle == 2)
					hors[y][hors[y][x].y].x--;	
				hors[y][x].is_obstacle = 0;
				verts[y][x].is_obstacle = 0;
			}
		}
	}

	return nrobs;
}

static void
PRINT_ALL(void)
{
	int i, x, y;

	puts("sequences");
	for(i=0; i<npossiblerobots; i++)
		printf("(%d %d %d %d) ", pospoints[i].x, pospoints[i].y, TRUE_VALUE(pospoints[i]), pospoints[i].is_obstacle);
	putchar('\n');

	puts("verts\n");
	for(y=0; y<h; y++) {
		for(x=0; x<w; x++) {
			printf("(%d %d %d) ", verts[y][x].x, verts[y][x].y, verts[y][x].is_obstacle);
		}
		putchar('\n');
	}

	puts("hors\n");
	for(y=0; y<h; y++) {
		for(x=0; x<w; x++) {
			printf("(%d %d %d) ", hors[y][x].x, hors[y][x].y, hors[y][x].is_obstacle);
		}
		putchar('\n');
	}

}

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

static int
compar_seqsizehor(const void *_a, const void *_b)
{
	int ta, tb;
	Point *a, *b;

	a = (Point *)_a;
	b = (Point *)_b;

	ta = TRUE_VALUE(*a);
	tb = TRUE_VALUE(*b);

	if(ta > tb) return -1;
	if(ta < tb) return 1;
	if(a->is_obstacle < b->is_obstacle) return -1;
	if(a->is_obstacle > b->is_obstacle) return 1;
	return 0;
}

static int
compar_seqsizevert(const void *_a, const void *_b)
{
	int ta, tb;
	Point *a, *b;

	a = (Point *)_a;
	b = (Point *)_b;

	ta = TRUE_VALUE(*a);
	tb = TRUE_VALUE(*b);

	if(ta > tb) return -1;
	if(ta < tb) return 1;
	if(a->is_obstacle < b->is_obstacle) return 1;
	if(a->is_obstacle > b->is_obstacle) return -1;
	return 0;
}

static void
doit(void)
{
	int i, x, y, nrobs2, nrobs1;

	/* width, height */
	scanf("%d %d", &h, &w);
	/* points of interest */
	scanf("%d", &npoints);
	for(i=0; i<npoints; i++) {
		scanf("%d %d", &points[i].y, &points[i].x);
		points[i].y--;
		points[i].x--;
		points[i].is_obstacle = 0;
		vertorder[i] = hororder[i] = &points[i];
	}

	/* obstacles */
	scanf("%d", &x);
	npoints += x;
	for(; i<npoints; i++) {
		scanf("%d %d", &points[i].y, &points[i].x);
		points[i].y--;
		points[i].x--;
		points[i].is_obstacle = 1;
		vertorder[i] = hororder[i] = &points[i];
	}

	qsort(vertorder, npoints, sizeof(Point *), compar_vert);
	qsort(hororder, npoints, sizeof(Point *), compar_hor);
	memset(hors, 0, sizeof(Point)*MAX_H*MAX_W);
	memset(verts, 0, sizeof(Point)*MAX_H*MAX_W);

	npossiblerobots = 0;
	
	/* create horizontal grid with info of all possible robots */
	for(i=0; i<npoints; ) {
		x = hororder[i]->x;
		y = hororder[i]->y;
		for(; i<npoints && !hororder[i]->is_obstacle && hororder[i]->y == y; i++) {
			hors[y][x].x ++;
			hors[y][hororder[i]->x].y = x;
			hors[y][hororder[i]->x].is_obstacle = 2;
		}
		pospoints[npossiblerobots].x = x;
		pospoints[npossiblerobots].y = y;
		pospoints[npossiblerobots].is_obstacle = 1;
		npossiblerobots++;
		for(; i<npoints && hororder[i]->is_obstacle; i++)
			hors[hororder[i]->y][hororder[i]->x].is_obstacle = 1;
	}

	/* vertical */
	for(i=0; i<npoints; ) {
		x = vertorder[i]->x;
		y = vertorder[i]->y;
		for(; i<npoints && !vertorder[i]->is_obstacle && vertorder[i]->x == x; i++) {
			verts[y][x].x ++;
			verts[vertorder[i]->y][x].y = y;
			verts[vertorder[i]->y][x].is_obstacle = 2;
		}
		pospoints[npossiblerobots].x = x;
		pospoints[npossiblerobots].y = y;
		pospoints[npossiblerobots].is_obstacle = 0;
		npossiblerobots++;
		for(; i<npoints && vertorder[i]->is_obstacle; i++)
			verts[vertorder[i]->y][vertorder[i]->x].is_obstacle = 1;
	}

	memcpy(verts2, verts, sizeof(Point)*MAX_W*MAX_H);
	memcpy(hors2, hors, sizeof(Point)*MAX_W*MAX_H);
	qsort(pospoints, npossiblerobots, sizeof(Point), compar_seqsizevert);
	nrobs1 = calc_response();

	memcpy(verts, verts2, sizeof(Point)*MAX_W*MAX_H);
	memcpy(hors, hors2, sizeof(Point)*MAX_W*MAX_H);
	qsort(pospoints, npossiblerobots, sizeof(Point), compar_seqsizehor);
	nrobs2 = calc_response();

	printf("%d\n", (nrobs1 < nrobs2 ? nrobs1 : nrobs2));
}

int
main()
{
	int n, i;

	scanf("%d", &n);
	for(i=0; i<n; i++)
		doit();
	return 0;
}
