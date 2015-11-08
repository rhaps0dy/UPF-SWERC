#include<iostream>
#include<cmath>
#include<vector>
#include<utility>
#include<limits>
#include<iomanip>

using namespace std;

#define X first
#define Y second

typedef long double LD;

pair<LD, LD> obstacles[10];

int main() {
	LD d;
	int n, b;
	cout << setprecision(7);
	while(cin >> d >> n >> b) {
		for(int i=0; i<n; i++)
			cin >> obstacles[i].X >> obstacles[i].Y;
		LD v_min = numeric_limits<LD>::infinity();
		for(int i=1; i<=b+1; i++) {
			LD vy2_max = 0., vx2_max;
			LD dist = d / (LD)i;
			for(int j=0; j<n; j++) {
				LD x_0 = floor(obstacles[j].X / dist) * dist,
					x = obstacles[j].X - x_0,
					y = obstacles[j].Y,
					x_d = x / dist,
					vy2 = y / (2*x_d * (1 - x_d));
				if(vy2 > vy2_max) {
					vx2_max = dist * dist / (4 * vy2);
					vy2_max = vy2;
				}
			}
			v_min = min(v_min, sqrt(vx2_max + vy2_max));
		}
		cout << v_min << endl;
	}
	return 0;
}
