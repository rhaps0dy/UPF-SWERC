#include <stdio.h>
#include <math.h>

#define sign(n) ((n) >> (sizeof(n) * 8 - 1))

int
main()
{
    int r1, c1, r2, c2, r3, c3, ncase, ydist, xdist, abs_xdist,
        abs_ydist, dist, xdistObstacle, ydistObstacle;

    for( ncase = 1
       ; scanf("%d %d %d %d %d %d", &r1, &c1, &r2, &c2, &r3, &c3) == 6
       ; ncase++
       ) {
        xdist = c2-c1;
        ydist = r2-r1;
        abs_xdist = abs(xdist);
        abs_ydist = abs(ydist);

        if(abs_xdist != abs_ydist || abs_xdist <= 1 || abs_ydist <= 1) {
            dist = (abs_xdist > abs_ydist ? abs_xdist : abs_ydist);
        } else /* if (xdist == ydist && xdist > 1 && ydist > 1) */ {
            xdistObstacle = c3-c1;
            ydistObstacle = r3-r1;
            /* if it sits in the diagonal and in between c1 and c2 */
            if(abs(xdistObstacle) == abs(ydistObstacle) &&
               sign(xdist) == sign(xdistObstacle) &&
               sign(ydist) == sign(ydistObstacle) &&
               abs(xdistObstacle) < abs_xdist) {
                dist = abs_xdist + 1;
            } else {
                dist = abs_xdist;
            }
        }
        printf("Case %d: %d\n", ncase, dist);
    }
    return 0;
}
