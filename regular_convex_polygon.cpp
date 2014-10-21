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
};

static N mod(Vec a) { return sqrtl(a.x*a.x + a.y*a.y); }
static Vec perp(Vec a) { return Vec(-a.y, a.x); }
N dot (Vec a, Vec b) { return a.x*b.x + a.y*b.y; }
Vec scale (Vec a, N n) { a.x*=n; a.y*=n; return a; }
Vec sub (Vec a, Vec b) { a.x-=b.x; a.y-=b.y; return a; }
Vec add (Vec a, Vec b) { a.x+=b.x; a.y+=b.y; return a; }

static Vec
calc_center(Vec a, Vec b, Vec c)
{
	Vec abm = scale(add(a, b), .5L);
	Vec bcm = scale(add(b, c), .5L);
	Vec v2 = scale(sub(c, b), .5L);
	Vec v1 = perp(scale(sub(a, b), .5L));
	return add(scale(v1, dot(sub(bcm, abm), v2)/dot(v2, v1)), abm);
}

int
main()
{
	N angab, angbc, diam, remab, rembc;
	Vec a, b, c, cen;

	while(scanf("%Lf %Lf %Lf %Lf %Lf %Lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) == 6) {
		cen = calc_center(a, b, c);
		diam = mod(sub(cen, a))*2.L;
		angab = asinl(fminl(mod(sub(a, b))/diam, 1.L));
		angbc = asinl(fminl(mod(sub(b, c))/diam, 1.L));
		for(int i=3; i<=1000; i++) {
			diam = M_PI / ((N)i);
			remab = angab - roundl(angab / diam) * diam;
			rembc = angbc - roundl(angbc / diam) * diam;
			if(IS_ZERO(remab) && IS_ZERO(rembc)) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}
