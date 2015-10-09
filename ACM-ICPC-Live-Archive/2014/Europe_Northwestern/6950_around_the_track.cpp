#include <utility>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

#define X first
#define Y second
#define LI long long
#define MP make_pair
#define PB push_back
#define SZ size()
#define SQ(a) ((a)*(a))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define FOR(i,x,y) for(int i=(int)x; i<(int)y; i++)
#define RFOR(i,x,y) for(int i=(int)x; i>(int)y; i--)
#define SORT(a) sort(a.begin(), a.end())
#define RSORT(a) sort(a.rbegin(), a.rend())
#define IN(a,pos,c) insert(a.begin()+pos,1,c)
#define DEL(a,pos,cant) erase(a.begin()+pos,cant)

typedef long double T;     // posiblemente cambiar a double
typedef pair<T,T> P;
T xp(P p, P q, P r) {
  return (q.X-p.X)*(r.Y-p.Y) - (r.X-p.X)*(q.Y-p.Y);
}
struct Vect {
  P p, q;  T dist;
  Vect(P &a, P &b) {
    p = a;  q = b;
    dist = SQ(a.X - b.X) + SQ(a.Y - b.Y);
  }
  bool operator<(const Vect &v) const {
    T t = xp(p, q, v.p);
    return t < 0 || t == 0 && dist < v.dist;
  }
};

vector<P> convexhull(vector<P> v) { // v.SZ >= 2
  sort(v.begin(), v.end());
  vector<Vect> u;
  for (int i = 1; i < (int)v.SZ; i++)
    u.PB(Vect(v[i], v[0]));
  sort(u.begin(), u.end());
  vector<P> w(v.SZ, v[0]);
  int j = 1;  w[1] = u[0].p;
  for (int i = 1; i < (int)u.SZ; i++) {
    T t = xp(w[j-1], w[j], u[i].p);
    for (j--; t < 0 && j > 0; j--)
      t = xp(w[j-1], w[j], u[i].p);
    j += t > 0 ? 2 : 1;
    w[j] = u[i].p;
  }
  w.resize(j+1);
  return w;
}

vector<P> vecs_of(const vector<P> &points) {
	int sz = points.SZ;
	vector<P> vecs(sz);
	for(int i=0; i<sz-1; i++) {
		vecs[i].X = points[i+1].X - points[i].X;
		vecs[i].Y = points[i+1].Y - points[i].Y;
	}
	vecs[sz-1].X = points[0].X - points[sz-1].X;
	vecs[sz-1].Y = points[0].Y - points[sz-1].Y;
	return vecs;
}

constexpr T PRECISION = 1e-6;

inline T norm(P v) {
	return sqrt(v.X * v.X + v.Y * v.Y);
}

int main () {
	int N, M;
	cout << setprecision(15);
	while(cin >> N) {
		vector<P> inner, outer;
		inner.resize(N);
		for(int i=N-1; i>=0; i--)
			cin >> inner[i].X >> inner[i].Y;
		
		cin >> M;
		outer.resize(M);
		for(int i=M-1; i>=0; i--)
			cin >> outer[i].X >> outer[i].Y;
	
		vector<P> chull = convexhull(inner);
		for(int i=0; i<(int)chull.SZ; i++)
			cout <<  inner[i].X << " " << inner[i].Y << " -> " << chull[i].X << " " <<chull[i].Y << endl;
		cout << "bler\n";
		
		vector<P> chull_vecs = vecs_of(chull);
		const vector<P> &outer_vecs = vecs_of(outer);

		T length = 0.0;
		int outer_sz = outer.SZ;
		for(int i=0; i<(int)chull.SZ; i++) {
			double min_t = 1.;
			int min_j = -1;
			const double Px = chull[i].X;
			const double Py = chull[i].Y;
			const double px = chull_vecs[i].X;
			const double py = chull_vecs[i].Y;
			for(int j=0; j<outer_sz; j++) {
				const double Qx = outer[j].X;
				const double Qy = outer[j].Y;
				const double qx = outer_vecs[j].X;
				const double qy = outer_vecs[j].Y;
				if((px == 0. && qy == 0.) || (py/px == qy/qx))
					continue;
				if(py/px == qy/qx)
					continue;
				double s, t;
				if(px != 0.) {
					double py_px = py/px;
					s = (Py - Qy + py_px *(Qx - Px)) / (qy - py_px * qx);
					t = (Qx - Px + qx*s) / px;
				} else {
					double px_py = px/py;
					s = (Px - Qx + px_py *(Qy - Py)) / (qx - px_py * qy);
					t = (Qy - Py + qy*s) / py;
				}
				if(s < PRECISION || s > 1-PRECISION || t < PRECISION || t > 1-PRECISION)
					continue;
				if(t < min_t) {
					min_t = t;
					min_j = j;
				}
			}
			if(min_j == -1) {
				length += norm(chull_vecs[i]);
				#ifndef ONLINE_JUDGE
				printf("Line (%lf, %lf)+s*(%lf, %lf) does not colide\n", Px, Py, px, py);
				#endif
				continue;
			}
				#ifndef ONLINE_JUDGE
			printf("Line (%lf, %lf)+s*(%lf, %lf) colides at %lf\n", Px, Py, px, py, min_t);
				#endif
			min_j = (min_j + 1) % outer_sz;
			
			T xprod_a = py * (outer[min_j].X-Px) - px * (outer[min_j].Y-Py);
			int next_j = (min_j + 1) % outer_sz;
			int good_j = (xprod_a < 0 ? min_j : next_j);
			int next_i = (i + 1) % ((int)chull.SZ);
			P next_vec(chull[next_i].X - outer[good_j].X, chull[next_i].Y - outer[good_j].Y);
			while(outer_vecs[good_j].Y * next_vec.X - outer_vecs[good_j].X * next_vec.Y < 0) {
				length += norm(outer_vecs[good_j]);
				good_j = (good_j + 1) % outer_sz;
				next_vec.X = chull[next_i].X - outer[good_j].X;
				next_vec.Y = chull[next_i].Y - outer[good_j].Y;
			}
			length += norm(P(outer[good_j].X - chull[i].X, outer[good_j].Y - chull[i].Y));
		}
		cout << length << endl;
	}
}
