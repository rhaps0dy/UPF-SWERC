#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

typedef uint32_t State;
using namespace std;

typedef struct {
    int x, y;
} Point;

State
encode_state(Point xys[4], int nRobots)
{
    int result = 0;
    for(int i=0; i<nRobots; i++) {
	result |= (xys[i].x & 0xf) << (i * 8);
	result |= (xys[i].y & 0xf) << (i * 8 + 4);
    }
    return result;
}

void
decode_state(State s, Point xys[4], int nRobots)
{
    for(int i=0; i < nRobots; i++) {
	xys[i].x = (s >> (i * 8)) & 0xf;
	xys[i].y = (s >> (i * 8 + 4)) & 0xf;
    }
}
