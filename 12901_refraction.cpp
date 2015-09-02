#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

#define SMALL_NUM (1e-8)

#define norm(x, y) sqrt((x)*(x) + (y)*(y))

int main()
{
    int T;
    cin >> T;
    cout << setprecision(4) << fixed;

    for(; T>0; T--) {
        double W, H, x, xe, ye, mu;
	cin >> W >> H >> x >> xe >> ye >> mu;

	double
	    e_vec_x = xe - W,
	    e_vec_y = ye - H;

	// if the eye is at the same height as the bowl, we will never see the coin
	if(e_vec_y < SMALL_NUM && e_vec_y > -SMALL_NUM) {
	    cout << "Impossible" << endl;
	    continue;
	}

	double eye_line_x_at_y_0 = W - H * e_vec_x / e_vec_y;

	if(eye_line_x_at_y_0 > x-SMALL_NUM) {
	    cout << 0.0 << endl;
	    continue;
	}

	double
	    sin_mpe = e_vec_x / norm(e_vec_x, e_vec_y),
	    a = e_vec_x / e_vec_y,
	    b = W - a*H - x,
	    s = sin_mpe / mu,
	    aa = a*a,
	    disc = s*(1 - s);

	if(disc < 0) {
	    cout << "Impossible" << endl;
	    continue;
	}

	disc = b * sqrt(disc);
	cout << disc << endl;

	double
	    minus_b = a * b * (1 - s),
	    divider = s + aa * s + aa,
	    h1 = (minus_b + disc) / divider,
	    h2 = (minus_b - disc) / divider;

	cout << "h1: " << divider << " h2: " << disc << endl;
	if(h1 > 0 && h1 <= H) {
	    cout << h1 << endl;
	} else if(h2 > 0 && h2 <= H) {
	    cout << h2 << endl;
	} else {
	    cout << "Impossible" << endl;
	}
    }
    return 0;
}
