#include <vector>
#include <cassert>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

#define SZ size()
#define PB push_back
#define LI long long

#define BASE 1000000000

struct big {
  vector<int> V;
	bool negative;
	big(): V(1, 0), negative(0) {}
	big(int n): V(1, abs(n)), negative(n < 0) {assert(n < BASE);}
	big(const big &b): V(b.V), negative(b.negative) {}

  bool operator==(const big &b) const { return V==b.V; }
  int &operator[](int i) { return V[i]; }
  int operator[](int i) const { return V[i]; }
  int size() const { return V.SZ; }
  void resize(int i) { V.resize(i); }

  bool abs_smaller(const big &b) const {
    for (int i = b.SZ-1; SZ == b.SZ && i >= 0; i--)
      if (V[i] == b[i]) continue;
      else return (V[i] < b[i]);
    return (SZ < b.SZ);
  }
	bool operator<(const big &b) const {
		if(b.negative && negative)
			return !abs_smaller(b);
		if(!b.negative && !negative)
			return abs_smaller(b);
		if(b.negative)
			return false;
		return true;
	}

  void add_digit(int l) {
    if (l > 0) V.PB(l);
  }
};

big operator*(const big &a, int b) {
  if (b == 0) return big(0);
  big c;  c.resize(a.SZ);
  c.negative = (a.negative && !(b < 0)) || (!a.negative && (b < 0));
  b = abs(b);
  LI l = 0;
  for (int i = 0; i < a.SZ; ++i) {
    l += (LI)b*a[i];
    c[i] = l%BASE;
    l /= BASE;
  }
  c.add_digit((int)l);
  return c;
}
big operator*(int b, const big &a) {return a*b;}

ostream &operator<<(ostream &os, const big &b) {
	if(b.negative)
		cout << '-';
  os << b[b.SZ-1];
  for (int k = b.SZ-2; k >= 0; k--)
    os << setw(9) << setfill('0') << b[k];
  return os;
}

int main() {
	big max_positive, max_negative, max;
	int n;
	bool beginning = true;
	while(scanf("%d", &n) == 1) {
		if(n == -999999) {
			cout << max << endl;
			beginning = true;
		} else {
			big m(n);
			if(beginning) {
				beginning = false;
				max = max_positive = max_negative = m;
				continue;
			}
			big a = max_positive * n;
			big b = max_negative * n;

			max_positive = m;
			if(max_positive < a)
				max_positive = a;
			if(max_positive < b)
				max_positive = b;

			max_negative = m;
			if(a < max_negative)
				max_negative = a;
			if(b < max_negative)
				max_negative = b;
			
			if(max < max_positive)
				max = max_positive;
		}
	}
	return 0;
}
