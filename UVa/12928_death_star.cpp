#include <cstdio>

struct Point {
    int x, y;
};

typedef Point Vector;

static Point pentagon[5];
static Point lines[5];

static bool
check_convex() {
    Vector a, b;
    for(int i=0; i<5; i++) {
        int j = (i+1)%5, k = (i+2)%5;
        a.x = pentagon[j].x - pentagon[i].x;
        a.y = pentagon[j].y - pentagon[i].y;
        b.x = pentagon[k].x - pentagon[j].x;
        b.y = pentagon[k].y - pentagon[j].y;
        int sin_ab = a.x * b.y - a.y * b.x;
        // 0 degrees <= angle <= 180 degrees
        if(sin_ab >= 0)
            return true;
    }
    return false;
}

static void
generate_triangles() {
    for(int i=0, j=2; i<5; i++, j++) {
        if(j > 4)
            j -= 5;
        lines[i].x = pentagon[j].x - pentagon[i].x;
        lines[i].y = pentagon[j].y - pentagon[i].y;
    }
}

// Check which side of every line the point is in, avoiding calculating a line
// twice.
static bool
inside_triangles(const Point p) {
    int sins[5];

    sins[0] = lines[0].x * (p.y - pentagon[0].y)
            - lines[0].y * (p.x - pentagon[0].x);
    sins[1] = lines[1].x * (p.y - pentagon[1].y)
            - lines[1].y * (p.x - pentagon[1].x);

    for(int i=2; i<5; i++) {
        sins[i] = lines[i].x * (p.y - pentagon[i].y)
                - lines[i].y * (p.x - pentagon[i].x);
        if(sins[i-2] <= 0 && sins[i-1] >= 0 && sins[i] <= 0)
            return true;
    }

    if(sins[4] <= 0 && sins[0] >= 0 && sins[1] <= 0)
        return true;
    if(sins[3] <= 0 && sins[4] >= 0 && sins[0] <= 0)
        return true;

    return false;
}

int
main() {
    Point bullets[100];
    int nbullets;

    while(scanf("%d %d", &pentagon[0].x, &pentagon[0].y) == 2) {
        for(int i=1; i<5; i++)
            scanf("%d %d", &pentagon[i].x, &pentagon[i].y);

        scanf("%d", &nbullets);
        for(int i=0; i<nbullets; i++)
            scanf("%d %d", &bullets[i].x, &bullets[i].y);

        if(check_convex()) {
            puts("Impossible");
            continue;
        }
        generate_triangles();
        for(int i=0; i<nbullets; i++) {
            if(inside_triangles(bullets[i]))
                puts("Yes");
            else
                puts("No");
        }
    }
    return 0;
}
