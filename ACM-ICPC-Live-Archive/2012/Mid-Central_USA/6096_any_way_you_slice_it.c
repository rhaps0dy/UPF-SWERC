#include <math.h>
#include <stdio.h>

typedef double F;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct {
    F vy, vx, x, y, length;
    int angle;
} lines[101];

static F
intersect(int i, int j) {
    if(fabs(lines[i].vy) <= 0.01) { /* prevent division by 0 */
	F py_px = lines[i].vy / lines[i].vx;
	return (lines[i].y - lines[j].y + py_px*(lines[j].x - lines[i].x)) / (lines[j].vy - py_px * lines[j].vx);
    } else {
	F px_py = lines[i].vx / lines[i].vy;
	return (lines[i].x - lines[j].x + px_py*(lines[j].y - lines[i].y)) / (lines[j].vx - px_py * lines[j].vy);
    }
}


int main()
{
    int N, i, angle, a, j;

    for(;;) {
	scanf("%d", &N);
	if(!N)
	    return 0;
	angle = 90;
	lines[0].x = lines[0].y = 0.;
	int fallen = 0;
	for(i=0; i<N; i++) {
	    scanf("%d %lf", &a, &lines[i].length);
	    if(!fallen) {
		angle += a;
		if(angle < 0) angle += 360;
		else if(angle >= 360) angle -= 360;
		double ang = (double)angle * M_PI / 180.;
		lines[i].angle = angle % 180;
		lines[i].vy = sin(ang);
		lines[i].vx = cos(ang);
		lines[i+1].x = lines[i].x + lines[i].vx * lines[i].length;
		lines[i+1].y = lines[i].y + lines[i].vy * lines[i].length;
		for(j=i-2; j>=0; j--) {
		    if(lines[i].angle == lines[j].angle)
			continue;

		    F len1 = intersect(i, j), len2 = intersect(j, i);
/*		    printf("(%lf, %lf) + %lf (%lf %lf) = (%lf, %lf) + %lf (%lf %lf)\n",
			   lines[i].x, lines[i].y, lines[i].length, lines[i].vx, lines[i].vy,
			   lines[j].x, lines[j].y, lines[j].length, lines[j].vx, lines[j].vy);
		    printf("len = %lf %lf\n", len1, len2);
		    putchar('\n');*/
		    if(len1 > 0. && len1 < lines[j].length && len2 > 0. && len2 < lines[i].length) {
			printf("%d\n", i+1);
			fallen = 1;
			break;
		    }
		}
	    }
	}
	if(!fallen)
	    puts("SAFE");
/*	else
	    for(i=0; i<N; i++)
		printf("(%lf, %lf) + %lf (%lf %lf)\n",
		lines[i].x, lines[i].y, lines[i].length, lines[i].vx, lines[i].vy);*/
    }
    return 0;
}
