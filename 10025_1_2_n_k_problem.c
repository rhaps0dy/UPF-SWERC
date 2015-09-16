#include <stdio.h>
#include <math.h>

int main() {
    int Ncases, k, n, k2, nn1;
    scanf("%d", &Ncases);
    while(Ncases--) {
	scanf("%d", &k);
	if(k==0) {
	    puts("3");
	} else {
	    k = (k > 0 ? k : -k);
	    k2 = k * 2;
	    n = (int)floor(sqrt((double)k2));
	    for(; (nn1 = n*(n+1)) < k2; n++);
	    if((nn1 / 2) % 2 == k % 2) {
		printf("%d\n", n);
	    } else {
		if(n % 2) {
		    n += 2;
		} else {
		    n += 1;
		}
		printf("%d\n", n);
	    }
	}
	if(Ncases)
	    putchar('\n');
    }
    return 0;
}
