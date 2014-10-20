#include <cmath>
#include <cstdio>

typedef long double N;

#define PRECISION 1e-7L
#define IS_ZERO(x) (x<PRECISION && x> -PRECISION)

typedef struct Vec Vec;
struct Vec {
	N x, y;

	Vec() {;}
	Vec(N a, N b) { x = a; y = b; }
	N operator* (Vec b) { return x*b.x + y*b.y; }
	Vec operator* (N a) { return Vec(x*a, y*a); }
	Vec operator- (Vec b) { return Vec(x-b.x, y-b.y); }
	Vec operator+ (Vec b) { return Vec(x+b.x, y+b.y); }
};

static N mod(Vec a) { return sqrtl(a.x*a.x + a.y*a.y); }
static Vec perp(Vec a) { return Vec(-a.y, a.x); }

static Vec
calc_center(Vec a, Vec b, Vec c)
{
	Vec abm = (a+b)*.5L;
	Vec bcm = (b+c)*.5L;
	Vec v2 = c-b;
	Vec v1 = a-b;
	return (v1 * (((bcm-abm)*v2)/(v2*v1))) + abm;
}

int
main()
{
	N angab, angbc, diam, remab, rembc;
	Vec a, b, c, cen;

	while(scanf("%Lf %Lf %Lf %Lf %Lf %Lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) == 6) {
		cen = calc_center(a, b, c);
		printf("%Lf %Lf\n", cen.x, cen.y);
		diam = mod(cen-a)*2.L;
		angab = asinl(fminl(mod(a-b)/diam, 1.L));
		angbc = asinl(fminl(mod(b-c)/diam, 1.L));
		for(int i=3; i<=1000; i++) {
			diam = M_PI / ((N)i);
			remab -= roundl(angab / diam) * diam;
			rembc -= roundl(angbc / diam) * diam;
			if(IS_ZERO(remab) && IS_ZERO(rembc)) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}
