#include <stdio.h>

typedef long double N;

#define P (probs[0][1])
#define _P (probs[1][0])

static N
calc_two_ahead_prob(N p)
{
	int i;
	N ini, tomul, sum;

	ini = p*p;
	tomul = 2*p*(1-p);
	sum = ini;

	while((ini=ini*tomul) > 1e-15)
		sum += ini;
	return sum;
}

static void
calc_rounds_prob(N *winp, N *evenp, N p, int npoints)
{
	N probs[npoints][npoints], sum;
	int i, j;

	P = p;
	_P = 1.L-p;

	for(i=2; i<npoints; i++)
		probs[0][i] = probs[0][i-1] * P;
	for(j=2; j<npoints; j++)
		probs[j][0] = probs[j-1][0] * _P;
	for(j=1; j<npoints; j++)
		for(i=1; i<npoints; i++)
			probs[j][i] = probs[j][i-1] * P + probs[j-1][i] * _P;

	*winp = 0.L;
	for(j=0; j<npoints-1; j++)
		*winp += probs[j][npoints-1] * P;
	*evenp = probs[npoints-1][npoints-1];
}

static void
doit(N p)
{
	N evenp, winp, aheadp, gamep, setp, tiebreakp, matchp;

	aheadp = calc_two_ahead_prob(p);
	calc_rounds_prob(&winp, &evenp, p, 4);
	gamep = winp+evenp*aheadp;

	calc_rounds_prob(&winp, &evenp, p, 7);
	tiebreakp = winp+evenp*aheadp;
	calc_rounds_prob(&winp, &evenp, gamep, 6);
	setp = winp + evenp*(gamep*gamep + 2.L*gamep*(1-gamep)*tiebreakp);
	calc_rounds_prob(&winp, &evenp, setp, 2);
	matchp = winp + evenp*setp;

	printf("%.11Lf %.11Lf %.11Lf\n", gamep, setp, matchp);
}

int
main()
{
	N p;

	for(;;) {
		scanf("%Lf", &p);
		if(p==-1.L) break;
		doit(p);
	}
	return 0;
}
