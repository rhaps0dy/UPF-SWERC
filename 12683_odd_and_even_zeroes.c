#include <stdio.h>

typedef long long N;

struct tabla {
	N n, par, impar;
} tabla [26];

int max;

int
search(N n)
{
	int i;

	for(i=max; i>0; i--)
		if(tabla[i].n <= n)
			break;
	max = i;
	return i;
}

int
main() 
{
	int i, ind, es_par;
	N n, total;

	tabla[0].n = 1;
	tabla[0].par = 1;
	tabla[0].impar = 0;

	for(i=1; i<26; i++) {
		tabla[i].n = tabla[i-1].n * 5;
		if((i-1)%2 == 0)
			tabla[i].par = tabla[i-1].par * 5;
		else
			tabla[i].par = tabla[i-1].par * 3 + tabla[i-1].impar * 2;
		tabla[i].impar = tabla[i].n - tabla[i].par;
	}

	for(;;) {
		scanf("%lld", &n);
		total = 0;
		es_par = 1;
		max = 25;

		if(n<0) break;

		while(n>=0) {
			ind = search(n);
			if(es_par)
				total += tabla[ind].par;
			else
				total += tabla[ind].impar;
			n -= tabla[ind].n;
			if(ind%2 == 1)
				es_par = !es_par;
		}

		printf("%lld\n", total);
	}
	return 0;
}
