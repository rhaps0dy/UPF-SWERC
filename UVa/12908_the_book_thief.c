#include <stdio.h>
#include <math.h>

int
main() {
    int s, y, y2, x2, ymin;
    while(scanf("%d", &s) && s != 0) {
        s *= 2;
        ymin = ((int) floor(sqrt((double) s))) - 1;
        for(y=ymin;
            (y2 = y*(y+1)) < s || (x2 = y2 - s) % 2 != 0 || x2 < 2;
            y++);
        printf("%d %d\n", x2/2, y);
    }
    return 0;    
}
