#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

constexpr double PRECISION = 1e-8;

inline double norm(double x, double y) { return sqrt(x*x + y*y); }

double v_walk, v_bike;

struct ternary {
public:
	double search(double a1, double a2, double bb1, double bb2) const {
		double b1=bb1, b2=bb2;
		while(fabs(a1-a2) > PRECISION) {
			double t1 = eval(a1, b1);
			double t2 = eval(a2, b1);
			if(t1 < t2) {
				a2 += (a1-a2)/3.;
			} else {
				a1 += (a2-a1)/3.;
			}
			b1=bb1, b2=bb2;
			while(fabs(b1-b2) > PRECISION) {
				double t1 = eval(a1, b1);
				double t2 = eval(a1, b2);
				if(t1 < t2) {
					b2 += (b1-b2)/3.;
				} else {
					b1 += (b2-b1)/3.;
				}
			}
		}
		return eval(a1, b1);
	}
	virtual double eval(double a, double b) const = 0;
};

struct diff_dim: public ternary {
public:
	double xa, xc, xd, ya, yb, yd;
	diff_dim(double _xa, double _xc, double _xd, double _ya, double _yb, double _yd)
		: xa(_xa), xc(_xc), xd(_xd), ya(_ya), yb(_yb), yd(_yd) {} //{printf("(%.0lf, %.0lf) to (x, %.0lf) to (%.0lf, x) to (%.0lf, %.0lf): ", xa, ya, yb, xc, xd, yd);}
	double eval(double xb, double yc) const {
		return (norm(xa-xb, ya-yb) + norm(xc-xd, yc-yd)) / v_walk + norm(xb-xc, yb-yc) / v_bike;
	}
};
struct same_dim: public ternary {
public:
	double xa, xb, xc, xd, ya, yd;
	same_dim(double _xa, double _xb, double _xc, double _xd, double _ya, double _yd)
		: xa(_xa), xb(_xb), xc(_xc), xd(_xd), ya(_ya), yd(_yd) {} // {printf("(%.0lf, %.0lf) to (%.0lf, x) to (%.0lf, x) to (%.0lf, %.0lf): ", xa, ya, xb, xc, xd, yd);}
	double eval(double yb, double yc) const {
		return (norm(xa-xb, ya-yb) + norm(xc-xd, yc-yd)) / v_walk + norm(xb-xc, yb-yc) / v_bike;
	}
};
struct with_station {
public:
	double xa, xb, xc, xd, ya, yb, yd;
	with_station(double _xa, double _xb, double _xc, double _xd, double _ya, double _yb, double _yd)
		: xa(_xa), xb(_xb), xc(_xc), xd(_xd), ya(_ya), yb(_yb), yd(_yd) {}
	double eval(double yc) const {
		return (norm(xa-xb, ya-yb) + norm(xc-xd, yc-yd)) / v_walk + norm(xb-xc, yb-yc) / v_bike;
	}
	double search(double a1, double a2) const {
		while(fabs(a1-a2) > PRECISION) {
			double t1 = eval(a1);
			double t2 = eval(a2);
			if(t1 < t2) {
				a2 += (a1-a2)/3.;
			} else {
				a1 += (a2-a1)/3.;
			}
		}
		return eval(a1);
	}
};


double stx[1000], sty[1000];
int main() {
	double xg, yg, xd, yd;
	double X1, Y1, X2, Y2;
	cout << setprecision(9);
	while(cin >> v_walk >> v_bike) {
		cin >> X1 >> Y1 >> X2 >> Y2;
		cin >> xg >> yg >> xd >> yd;
		double min_time = norm(xd-xg, yd-yg) / v_walk;
		int n_stations;
		cin >> n_stations;
		for(int i=0; i<n_stations; i++)
			cin >> stx[i] >> sty[i];
		for(int i=0; i<n_stations; i++)
			for(int j=0; j<n_stations; j++) {
				if(j==i) continue;
				double t = (norm(stx[i]-xg, sty[i]-yg) + norm(stx[j]-xd, sty[j]-yd)) / v_walk + norm(stx[i]-stx[j], sty[i]-sty[j]) / v_bike;
				if(t < min_time) min_time = t;
			}
		min_time = min(min_time, diff_dim(xg, X1, xd, yg, Y1, yd).search(X1, X2, Y1, Y2));
		min_time = min(min_time, diff_dim(xg, X2, xd, yg, Y1, yd).search(X1, X2, Y1, Y2));
		min_time = min(min_time, diff_dim(xg, X1, xd, yg, Y2, yd).search(X1, X2, Y1, Y2));
		min_time = min(min_time, diff_dim(xg, X2, xd, yg, Y2, yd).search(X1, X2, Y1, Y2));
		min_time = min(min_time, diff_dim(xd, X1, xg, yd, Y1, yg).search(X1, X2, Y1, Y2));
		min_time = min(min_time, diff_dim(xd, X2, xg, yd, Y1, yg).search(X1, X2, Y1, Y2));
		min_time = min(min_time, diff_dim(xd, X1, xg, yd, Y2, yg).search(X1, X2, Y1, Y2));
		min_time = min(min_time, diff_dim(xd, X2, xg, yd, Y2, yg).search(X1, X2, Y1, Y2));

		min_time = min(min_time, same_dim(xd, X1, X2, xg, yd, yg).search(Y1, Y2, Y1, Y2));
		min_time = min(min_time, same_dim(xg, X1, X2, xd, yg, yd).search(Y1, Y2, Y1, Y2));
		min_time = min(min_time, same_dim(yd, Y1, Y2, yg, xd, xg).search(X1, X2, X1, X2));
		min_time = min(min_time, same_dim(yg, Y1, Y2, yd, xg, xd).search(X1, X2, X1, X2));

		min_time = min(min_time, same_dim(xd, X1, X1, xg, yd, yg).search(Y1, Y2, Y1, Y2));
		min_time = min(min_time, same_dim(xg, X1, X1, xd, yg, yd).search(Y1, Y2, Y1, Y2));
		min_time = min(min_time, same_dim(xg, X2, X2, xd, yg, yd).search(Y1, Y2, Y1, Y2));
		min_time = min(min_time, same_dim(xd, X2, X2, xg, yd, yg).search(Y1, Y2, Y1, Y2));
		min_time = min(min_time, same_dim(yd, Y1, Y1, yg, xd, xg).search(X1, X2, X1, X2));
		min_time = min(min_time, same_dim(yg, Y1, Y1, yd, xg, xd).search(X1, X2, X1, X2));
		min_time = min(min_time, same_dim(yg, Y2, Y2, yd, xg, xd).search(X1, X2, X1, X2));
		min_time = min(min_time, same_dim(yd, Y2, Y2, yg, xd, xg).search(X1, X2, X1, X2));

		for(int i=0; i<n_stations; i++) {
			min_time = min(min_time, with_station(xd, stx[i], X1, xg, yd, sty[i], yg).search(Y1, Y2));
			min_time = min(min_time, with_station(xd, stx[i], X2, xg, yd, sty[i], yg).search(Y1, Y2));
			min_time = min(min_time, with_station(yd, sty[i], Y1, yg, xd, stx[i], xg).search(X1, X2));
			min_time = min(min_time, with_station(yd, sty[i], Y2, yg, xd, stx[i], xg).search(X1, X2));
			min_time = min(min_time, with_station(xg, stx[i], X1, xd, yg, sty[i], yd).search(Y1, Y2));
			min_time = min(min_time, with_station(xg, stx[i], X2, xd, yg, sty[i], yd).search(Y1, Y2));
			min_time = min(min_time, with_station(yg, sty[i], Y1, yd, xg, stx[i], xd).search(X1, X2));
			min_time = min(min_time, with_station(yg, sty[i], Y2, yd, xg, stx[i], xd).search(X1, X2));
		}

		cout << min_time << endl;
	}
	return 0;
}
