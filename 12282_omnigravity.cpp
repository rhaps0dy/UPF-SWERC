#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>

#define X first
#define Y second
#define MP make_pair

using namespace std;

typedef int State;
typedef vector<pair<int, int> > Board;
typedef enum {
    Gravity_North = 0,
    Gravity_West = 1,
    Gravity_East = 2,
    Gravity_South = 3
} Gravity;

static State
coordsToState(int x[4], int y[4])
{
    State s = 0;

    for(int i=0; i<4; i++) {
        int d = 6*i;
        s |= (x[i] & 0x7) << d;
        s |= (y[i] & 0x7) << (d + 3);
    }

    return s;
}

static void
stateToCoords(int x[4], int y[4], State s)
{
    for(int i=0; i<4; i++) {
        int d = 6*i;
        x[i] = (s & (0x7 << d)) >> d;
        d += 3;
        y[i] = (s & (0x7 << d)) >> d;
    }
}

static void
ensure_order_of(int x[], int y[], int order[], int i) {
    if(x[i] > x[i+1]) {
        int temp;
        temp = x[i];
        x[i] = x[i+1];
        x[i+1] = temp;
        temp = y[i];
        y[i] = y[i+1];
        y[i+1] = temp;
        temp = order[i];
        order[i] = order[i+1];
        order[i+1] = temp;
    }
}

State
transition(Board &b, State s, Gravity g)
{
    int x[4], y[4], order[4];
    stateToCoords(x, y, s);

    for(int i=0; i<4; i++)
        order[i] = i;

    if(g == Gravity_West || g == Gravity_East) {
        // sort horizontally, merge sort
        for(int i=0; i<2; i++)
            ensure_order_of(x, y, order, i*2);
        for(int i=0; i<3; i++)
            ensure_order_of(x, y, order, i);
    } else {
        // sort vertically
        for(int i=0; i<2; i++)
            ensure_order_of(y, x, order, i*2);
        for(int i=0; i<3; i++)
            ensure_order_of(y, x, order, i);
    }

    if(g == Gravity_North) {
        // for all blocks
        for(int i=0; i<4; i++) {
            // check obstacles in decreasing y order
            int collided_block = -1, collided_obstacle = -1; // highest we can go
            for(int j = ((int)b.size()) - 1; j>=0; j--) {
                if(b[j].Y < y[i] && (b[j].X == x[i] || b[j].X == x[i]+1)) {
                    collided_obstacle = b[j].Y;
                    break;
                }
            }
            // check blocks in decreasing y order
            for(int j=i-1; j>=0; j--) {
                if(x[j] == x[i] || x[j] == x[i] - 1 || x[j] == x[i] + 1) {
                    collided_block = y[j] + 1;
                    break;
                }
            }
            y[i] = max(collided_obstacle, collided_block) + 1;
        }
    } else if(g == Gravity_South) {
        // for all blocks
        for(int i=3; i>=0; i--) {
            // check obstacles in increasing y order
            int collided_block = 8, collided_obstacle = 8; // lowest we can go
            for(int j = 0; j<(int)b.size(); j++) {
                if(b[j].Y > y[i] && (b[j].X == x[i] || b[j].X == x[i]+1)) {
                    collided_obstacle = b[j].Y;
                    break;
                }
            }
            // check blocks in increasing y order
            for(int j=i+1; j<4; j++) {
                if(x[j] == x[i] || x[j] == x[i] - 1 || x[j] == x[i] + 1) {
                    collided_block = y[j];
                    break;
                }
            }
            y[i] = min(collided_obstacle, collided_block) - 2;
        }
    }else if(g == Gravity_West) {
        // for all blocks
        for(int i=0; i<4; i++) {
            // check obstacles in decreasing x order
            int collided_block = -1, collided_obstacle = -1; // highest we can go
            for(int j = ((int)b.size()) - 1; j>=0; j--) {
                if(b[j].X < x[i] && (b[j].Y == y[i] || b[j].Y == y[i]+1)) {
                    collided_obstacle = b[j].X;
                    break;
                }
            }
            // check blocks in decreasing x order
            for(int j=i-1; j>=0; j--) {
                if(y[j] == y[i] || y[j] == y[i] - 1 || y[j] == y[i] + 1) {
                    collided_block = x[j] + 1;
                    break;
                }
            }
            x[i] = max(collided_obstacle, collided_block) + 1;
        }
    } else if(g == Gravity_East) {
        // for all blocks
        for(int i=3; i>=0; i--) {
            // check obstacles in increasing x order
            int collided_block = 8, collided_obstacle = 8; // lowest we can go
            for(int j = 0; j<(int)b.size(); j++) {
                if(b[j].X > x[i] && (b[j].Y == y[i] || b[j].Y == y[i]+1)) {
                    collided_obstacle = b[j].X;
                    break;
                }
            }
            // check blocks in increasing x order
            for(int j=i+1; j<4; j++) {
                if(y[j] == y[i] || y[j] == y[i] - 1 || y[j] == y[i] + 1) {
                    collided_block = x[j];
                    break;
                }
            }
            x[i] = min(collided_obstacle, collided_block) - 2;
        }
    }
    int new_x[4], new_y[4];
    for(int i=0; i<4; i++) {
        new_x[i] = x[order[i]];
        new_y[i] = y[order[i]];
    }
    return coordsToState(new_x, new_y);
}

int main()
{
    int x[4], y[4];
    vector<pair<int, int> > obstacles;
    State s;

    obstacles.push_back(MP(1,0));
    obstacles.push_back(MP(4,0));
    obstacles.push_back(MP(3,3));
    obstacles.push_back(MP(7,2));
    obstacles.push_back(MP(0,6));
    obstacles.push_back(MP(5,5));


    x[0] = 0;
    y[0] = 1;
    x[1] = 4;
    y[1] = 3;
    x[2] = 1;
    y[2] = 5;
    x[3] = 4;
    y[3] = 6;
    s = coordsToState(x, y);
    stateToCoords(x, y, transition(obstacles, s, Gravity_North));
    printf("North: (%d %d) (%d %d) (%d %d) (%d %d)\n", x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3]);
    stateToCoords(x, y, transition(obstacles, s, Gravity_East));
    printf("East: (%d %d) (%d %d) (%d %d) (%d %d)\n", x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3]);
    stateToCoords(x, y, transition(obstacles, s, Gravity_South));
    printf("South: (%d %d) (%d %d) (%d %d) (%d %d)\n", x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3]);
    stateToCoords(x, y, transition(obstacles, s, Gravity_West));
    printf("West: (%d %d) (%d %d) (%d %d) (%d %d)\n", x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3]);
    return 0;
}
