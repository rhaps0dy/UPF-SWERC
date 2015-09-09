#include <stdio.h>
#include <math.h>

#define MAX_CREDITS 160

double n_students[MAX_CREDITS];

struct {
    int a, b, c;
    double cost;
} record;

static void
calculate_record(int a, double N) {
    int b, c;
    double cost, Ngroup;
    Ngroup = N/4;
    for(b=a+1; b <= MAX_CREDITS-2; b++) {
        for(c=b+1; c <= MAX_CREDITS-1; c++) {
            cost = fabs(n_students[a] - Ngroup);
            cost += fabs(n_students[b] - n_students[a] - Ngroup);
            cost += fabs(n_students[c] - n_students[b] - Ngroup);
            cost += fabs(N - n_students[c] - Ngroup);
            if(cost < record.cost) {
                record.a = a;
                record.b = b;
                record.c = c;
                record.cost = cost;
            }
        }
    }
}


int main() {
    int T, credits, ncase, i, a, a_immediately_greater;
    double N, a_students;

    scanf("%d", &T);
    for(ncase=1; ncase<=T; ncase++) {
        for(i=0; i<MAX_CREDITS; i++)
            n_students[i] = 0.0;
        scanf("%lf", &N);
        for(i=N; i--; ) {
            scanf("%d", &credits);
            n_students[credits] += 1.0;
        }

        /* calculate cumulative sum */
        for(i=1; i<MAX_CREDITS; i++)
            n_students[i] += n_students[i-1];

        /* set a to the first index with cutoff immediately greater to N/4 */
        for(a=0; a<MAX_CREDITS && n_students[a] < N/4; a++);
        a_immediately_greater = a;

        /* set a to the first index with cutoff immediately greater to N/4 */
        if(a != 0) {
            a--;
            a_students = n_students[a];
            for(; a>0 && n_students[a] == a_students; a--);
            a++;
        }

        /* max cost is < 10000 */
        record.cost = 99999999.;
        calculate_record(a, N);
        calculate_record(a_immediately_greater, N);

        printf("Case %d: %d %d %d\n", ncase, record.a, record.b, record.c);
    }
    return 0;
}
