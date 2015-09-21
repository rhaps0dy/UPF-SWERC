#include <iostream>
#include <string.h>
#include <stdlib.h>

#include <cassert>
#include <cstdio>
#include <cmath>

using namespace std;

// we use the nearest upper power of 2 to 200k
#define MAX_DIST (262144*2)

struct cpx
{
  cpx(){}
  cpx(double aa):a(aa){}
  cpx(double aa, double bb):a(aa),b(bb){}
  double a;
  double b;
  double modsq(void) const
  {
    return a * a + b * b;
  }
  cpx bar(void) const
  {
    return cpx(a, -b);
  }
};

cpx operator +(cpx a, cpx b)
{
  return cpx(a.a + b.a, a.b + b.b);
}

cpx operator *(cpx a, cpx b)
{
  return cpx(a.a * b.a - a.b * b.b, a.a * b.b + a.b * b.a);
}

cpx operator /(cpx a, cpx b)
{
  cpx r = a * b.bar();
  return cpx(r.a / b.modsq(), r.b / b.modsq());
}

cpx EXP(double theta)
{
  return cpx(cos(theta),sin(theta));
}

const double two_pi = 4 * acos(0);

cpx distances[MAX_DIST];
cpx fftOut[MAX_DIST];
int maxDist;


// from Stanford's notebook: https://web.stanford.edu/~liszt90/acm/notebook.html
// in:     input array
// out:    output array
// step:   {SET TO 1} (used internally)
// size:   length of the input/output {MUST BE A POWER OF 2}
// dir:    either plus or minus one (direction of the FFT)
// RESULT: out[k] = \sum_{j=0}^{size - 1} in[j] * exp(dir * 2pi * i * j * k / size)
void FFT(cpx *in, cpx *out, int step, int size, int dir)
{
  if(size < 1) return;
  if(size == 1)
  {
    out[0] = in[0];
    return;
  }
  FFT(in, out, step * 2, size / 2, dir);
  FFT(in + step, out + size / 2, step * 2, size / 2, dir);
  for(int i = 0 ; i < size / 2 ; i++)
  {
    cpx even = out[i];
    cpx odd = out[i + size / 2];
    out[i] = even + EXP(dir * two_pi * i / size) * odd;
    out[i + size / 2] = even + EXP(dir * two_pi * (i + size / 2) / size) * odd;
  }
}


int
main()
{
    int N, d;
    cpx cpx_1(1);
    
    while(cin >> N) {
	maxDist = 0;
	memset(distances, 0, MAX_DIST*sizeof(cpx));

	distances[0] = cpx_1; // permit one shots

	for(int i=0; i<N; i++) {
	    cin >> d;
	    if(d > maxDist)
		maxDist = d;
	    distances[d] = cpx_1;
	}

	// Find (nearest upper power of 2) * 2. O(log 200k)
	int shiftAmount;
	for(shiftAmount = 0; (maxDist >> shiftAmount) != 0; shiftAmount++);
	maxDist = 1 << (shiftAmount + 1);

	FFT(distances, fftOut, 1, maxDist, 1);
	for(int i=0; i<maxDist; i++)
	    fftOut[i] = fftOut[i] * fftOut[i];
	FFT(fftOut, distances, 1, maxDist, -1);


	cin >> N;
	int total = 0;
	for(int i=0; i<N; i++) {
	    cin >> d;
	    if(distances[d].a > 0.01)
		total++;
	}
	cout << total << endl;
    }
    return 0;
}
