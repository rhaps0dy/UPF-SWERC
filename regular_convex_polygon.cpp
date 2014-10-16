#include <cmath>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>

#define X first
#define Y second

using namespace std;
typedef pair<double, double> Point;
typedef Point Vector;

#define IS_ZERO(d) (d>-0.000001 && d < 0.000001)

Point
calc_center(double ax, double ay, double bx, double by, double cx, double cy)
{
	double amx, amy, a_x, a_y, bmx, bmy, b_x, b_y, m, n, x, y;

	amx = -by+ay;
	amy = bx-ax;
	a_x = (ax+bx)/2.;
	a_y = (ay+by)/2.;

	bmx = -cy+by;
	bmy = cx-bx;
	b_x = (bx+cx)/2.;
	b_y = (by+cy)/2.;

	if(IS_ZERO(amx)) {
		if(IS_ZERO(bmy)) {
			return make_pair(a_x, b_y);
		} else {
			// bmx*m + b_x = a_x;
			m = (a_x-b_x/bmx);
			return make_pair(a_x, b_y+bmy*m);
		}
	}
	if(IS_ZERO(bmx)) {
		if(IS_ZERO(amy)) {
			return make_pair(b_x, a_y);
		} else {
			// amx*n + a_x = b_x;
			n = (b_x-a_x/amx);
			return make_pair(b_x, a_y+amy*n);
		}
	}

	n = ((bmy/bmx)*(a_x-b_x) + b_y - a_y)/(amy - bmy/bmx*amx);
	m = (amx*n + a_x - b_x) / bmx;

	x = amx*n+a_x;
	y = amy*n+a_y;

	x = bmx*m+b_x;
	y = bmy*m+b_y;

	return make_pair(x, y);
}

static double
angle_with_xaxis(Vector v)
{
	double n;
	if(IS_ZERO(v.Y)) {
		if(v.X < 0.0) return M_PI;
		return 0.0;
	}
	if(IS_ZERO(v.X)) {
		if(v.Y < 0.0) return 3.*M_PI/2.;
		return M_PI/2.;
	}
	n = (v.X < 0 ? -v.X : v.X)/sqrt(v.X*v.X + v.Y*v.Y);
	if(v.X > 0) {
		if(v.Y > 0)
			return acos(n);
		return 2*M_PI-acos(n);
	} else {
		if(v.Y > 0)
			return M_PI-acos(n);
		return M_PI+acos(n);
	}
}

static double
gcd(double a, double b)
{
	double c;
	for(;;) {
		for(c=a; c>=b; c-=b);
		if(IS_ZERO(c)) return b;
		a = b;
		b = c;
	}
	return b;
}

static double
calc_biggest_angle_portion(Vector a, Vector b, Vector c)
{
	vector<double> angs;
	int ns[3], i;
	double d;

	angs.push_back(angle_with_xaxis(a));
	angs.push_back(angle_with_xaxis(b));
	angs.push_back(angle_with_xaxis(c));
	sort(angs.begin(), angs.end());
	d = angs[2];
	angs[2] -= angs[1];
	angs[1] -= angs[0];
	angs[0] = angs[0]+M_PI*2-d;
	return gcd(gcd(angs[2], angs[1]), angs[0]);
}

int
main()
{
	double ax, ay, bx, by, cx, cy;
	string s;

	while(getline(cin, s)) {
		if(s=="END") return 0;
		istringstream iss(s);
		iss >> ax >> ay;
		cin >> bx >> by;
		cin >> cx >> cy;
		getline(cin, s);

		Point p = calc_center(ax, ay, bx, by, cx, cy);

		Vector a, b, c;
		a.X = (ax - p.X);
		a.Y = (ay - p.Y);
		b.X = (bx - p.X);
		b.Y = (by - p.Y);
		c.X = (cx - p.X);
		c.Y = (cy - p.Y);

		/* now get smallest angles between them */
		double ang = calc_biggest_angle_portion(a,b,c);
		double res = 2*M_PI/ang;
		printf("%.0f\n", res);
	}
	return 0;
}
