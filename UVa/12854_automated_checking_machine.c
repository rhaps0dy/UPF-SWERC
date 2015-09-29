#include <stdio.h>

int main() {
    int a[5];
    int b[5];
    int i;
    while(scanf("%d %d %d %d %d", a, a+1, a+2, a+3, a+4) == 5) {
	scanf("%d %d %d %d %d", b, b+1, b+2, b+3, b+4);
	int is_compatible = 1;
	for(i=0; i<5; i++) {
	    if(a[i] == b[i]) {
		is_compatible = 0;
		break;
	    }
	}
	if(is_compatible)
	    puts("Y");
	else
	    puts("N");
    }
    return 0;
}
