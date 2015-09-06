#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <map>

typedef uint32_t State;
using namespace std;

typedef struct {
    int x, y;
} Point;

enum Movement {UP, DOWN, LEFT, RIGHT};

bool table[10][10];
int width, height, bound;
Point goal;

void printState(Point xys[4], int nRobots)
{
    for (int i = 0; i < nRobots; ++i)
    {
        cout << i << " - x: " << xys[i].x << " - y: " << xys[i].y << endl;
    }
}

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

State transition(State s, Movement m, int r, int nRobots)
{
    Point xys[4];
    decode_state(s, xys, nRobots);

    if (m == UP)
    {
        int targety = 0;
        int row = xys[r].x;
    
        // Check collision with robots
        for (int i = 0; i < nRobots; ++i)
        {
            if (i != r)
            {
                if (row == xys[i].x && xys[r].y > xys[i].y && targety < xys[i].y + 1)
                {
                    targety = xys[i].y + 1;
                }
            }
        }
        
        // Check collision with walls
        for (int i = xys[r].y - 1; i >= targety; --i)
        {
            if (table[i][row] && targety < i + 1)
            {
                targety = i + 1;
            }
        }
        
        xys[r].y = targety;
    }
    else if (m == DOWN)
    {
        int targety = height - 1;
        int row = xys[r].x;
    
        // Check collision with robots
        for (int i = 0; i < nRobots; ++i)
        {
            if (i != r)
            {
                if (row == xys[i].x && xys[r].y < xys[i].y && targety > xys[i].y - 1)
                {
                    targety = xys[i].y - 1;
                }
            }
        }
        
        // Check collision with walls
        for (int i = xys[r].y + 1; i <= targety; ++i)
        {
            if (table[i][row] && targety > i - 1)
            {
                targety = i - 1;
            }
        }
        
        xys[r].y = targety;
    }
    else if (m == LEFT)
    {
        int targetx = 0;
        int column = xys[r].y;
    
        // Check collision with robots
        for (int i = 0; i < nRobots; ++i)
        {
            if (i != r)
            {
                if (column == xys[i].y && xys[r].x > xys[i].x && targetx < xys[i].y + 1)
                {
                    targetx = xys[i].x + 1;
                }
            }
        }
        
        // Check collision with walls
        for (int i = targetx; i < xys[r].x; ++i)
        {
            if (table[column][i] && targetx < i + 1)
            {
                targetx = i + 1;
            }
        }
        
        xys[r].x = targetx;
    }
    else if (m == RIGHT)
    {
        int targetx = width - 1;
        int column = xys[r].y;
    
        // Check collision with robots
        for (int i = 0; i < nRobots; ++i)
        {
            if (i != r)
            {
                if (column == xys[i].y && xys[r].x < xys[i].x && targetx > xys[i].y - 1)
                {
                    targetx = xys[i].x - 1;
                }
            }
        }
        
        // Check collision with walls
        for (int i = xys[r].x; i <= targetx; ++i)
        {
            if (table[column][i] && targetx > i - 1)
            {
                targetx = i - 1;
            }
        }
        
        xys[r].x = targetx;
    }
    
    //printState(xys, nRobots);
    
    return encode_state(xys, nRobots);
}

bool isTerminal(State s, int nRobots)
{
    Point xys[4];
    decode_state(s, xys, nRobots);
    
    return xys[0].x == goal.x && xys[0].y == goal.y;
}

int
bfs(State s, int nRobots)
{
    queue< pair<State, int> > states;
    states.push(make_pair(s, 0));
    
    map<State, bool> cache;
    cache.insert(make_pair(s, true));

    while (true)
    {    
        pair<State, int> statepair = states.front();
        State s = statepair.first;
    
        if (statepair.second >= bound)
        {
            return -1;
        }
    
        for (int i = 0; i < nRobots; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                State sp = transition(s, (Movement)j, i, nRobots);

                if (cache.find(sp) == cache.end())
                {                
                    if (isTerminal(sp, nRobots))
                    {  
                        return statepair.second + 1;
                    }
                    else if (s != sp)
                    {                
                        states.push(make_pair(sp, statepair.second + 1));
                    }
                    
                    cache.insert(make_pair(sp, true));
                }
            }
        }
        
        states.pop();
        
        if (states.empty())
        {
            return -1;
        }
    }
}

int
main()
{
    int nRobots = 0;

    Point statep[4];

    while (cin >> nRobots >> width >> height >> bound)
    {
        char aux;
    
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                cin >> aux;
                
                if (aux == '.')
                {
                    table[i][j] = false;
                }
                else if (aux == 'X')
                {
                    goal.x = j;
                    goal.y = i;
                    table[i][j] = false;
                }
                else if (aux == 'W')
                {
                    table[i][j] = true;
                }
                else if (aux >= '1' && aux <= '4')
                {
                    int num = aux - '1';
                    statep[num].x = j;
                    statep[num].y = i;
                    table[i][j] = false;
                }
            }
        }
        
        State s = encode_state(statep, nRobots);
        
        int depth = bfs(s, nRobots);

        if (depth == -1)
        {
            cout << "NO SOLUTION\n";
        }
        else
        {
            cout << depth << "\n";
        }
    }

    return 0;
}

