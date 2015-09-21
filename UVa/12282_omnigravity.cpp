#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <cstdlib>

#define X first
#define Y second
#define MP make_pair
#define PB push_back
#define SZ size()

#define MAX_STATE 16777217
#define NUM_GRAV 4

using namespace std;

typedef int State;
typedef vector<pair<int, int> > Board;
typedef enum {
    Gravity_North = 0,
    Gravity_West = 1,
    Gravity_East = 2,
    Gravity_South = 3
} Gravity;

bool sort_pred(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return left.second < right.second;
    }

bool V[MAX_STATE];

int N = 0; //num states

Board horizBoard;
Board vertBoard;

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
        // sort horizontally, bubble sort
        for(int j=0; j<4; j++)
            for(int i=0; i<3; i++)
                ensure_order_of(x, y, order, i);
    } else {
        // sort vertically, bubble sort
        for(int j=0; j<4; j++)
            for(int i=0; i<3; i++)
                ensure_order_of(y, x, order, i);
    }
    
   /* cout << "X: ";
    for(int i=0; i<4; i++)
       cout << x[i] << ", ";
    cout << endl;
    cout << "Y: ";
    for(int i=0; i<4; i++)
       cout << y[i] << ", ";
    cout << endl;
    cout << "ORDER: ";
    for(int i=0; i<4; i++)
       cout << order[i] << ", ";
    cout << endl << endl; */

    if(g == Gravity_North) {
        // for all blocks
        for(int i=0; i<4; i++) {
            // check obstacles in decreasing y order
            int collided = -1; // highest we can go
            for(int j = ((int)b.size()) - 1; j>=0; j--) {
                if(b[j].Y < y[i] && (b[j].X == x[i] || b[j].X == x[i]+1)) {
                    collided = b[j].Y;
                    break;
                }
            }
            // check blocks in decreasing y order
            for(int j=i-1; j>=0; j--) {
                if(x[j] == x[i] || x[j] == x[i] - 1 || x[j] == x[i] + 1) {
                    collided = max(collided, y[j] + 1);
                }
            }
            y[i] = collided + 1;
        }
    } else if(g == Gravity_South) {
        // for all blocks
        for(int i=3; i>=0; i--) {
            // check obstacles in increasing y order
            int collided = 8; // lowest we can go
            for(int j = 0; j<(int)b.size(); j++) {
                if(b[j].Y > y[i] && (b[j].X == x[i] || b[j].X == x[i]+1)) {
                    collided = b[j].Y;
                    break;
                }
            }
            // check blocks in increasing y order
            for(int j=i+1; j<4; j++) {
                if(x[j] == x[i] || x[j] == x[i] - 1 || x[j] == x[i] + 1) {
                    collided = min(collided, y[j]);
                }
            }
            y[i] = collided - 2;
        }
    }else if(g == Gravity_West) {
        // for all blocks
        for(int i=0; i<4; i++) {
            // check obstacles in decreasing x order
            int collided = -1; // highest we can go
            for(int j = ((int)b.size()) - 1; j>=0; j--) {
                if(b[j].X < x[i] && (b[j].Y == y[i] || b[j].Y == y[i]+1)) {
                    collided = b[j].X;
                    break;
                }
            }
            // check blocks in decreasing x order
            for(int j=i-1; j>=0; j--) {
                if(y[j] == y[i] || y[j] == y[i] - 1 || y[j] == y[i] + 1) {
                    collided = max(collided, x[j] + 1);
                }
            }
            x[i] = collided + 1;
        }
    } else if(g == Gravity_East) {
        // for all blocks
        for(int i=3; i>=0; i--) {
            // check obstacles in increasing x order
            int collided = 8; // lowest we can go
            for(int j = 0; j<(int)b.size(); j++) {
                if(b[j].X > x[i] && (b[j].Y == y[i] || b[j].Y == y[i]+1)) {
                    collided = b[j].X;
                    break;
                }
            }
            // check blocks in increasing x order
            for(int j=i+1; j<4; j++) {
                if(y[j] == y[i] || y[j] == y[i] - 1 || y[j] == y[i] + 1) {
                    collided = min(collided, x[j]);
                }
            }
            x[i] = collided - 2;
        }
    }
    int new_x[4], new_y[4];
    for(int i=0; i<4; i++) {
        new_x[order[i]] = x[i];
        new_y[order[i]] = y[i];
    }
    return coordsToState(new_x, new_y);
}

void findNumStates(State s)
{
    for (int g = 0; g < NUM_GRAV; ++g)
    {
        State sp = 0;
        
        if(g == Gravity_North || g == Gravity_South)
        {
            sp = transition(vertBoard, s, (Gravity)g);
        }
        else
        {
            sp = transition(horizBoard, s, (Gravity)g);
        }
        
      /*  int x[4],y[4];
        
        stateToCoords(x,y,sp);
        
        cout << "A: " << x[0] << "," << y[0] << "\n"; 
        cout << "B: " << x[1] << "," << y[1] << "\n"; 
        cout << "C: " << x[2] << "," << y[2] << "\n"; 
        cout << "D: " << x[3] << "," << y[3] << "\n"; 
        cout << "\n"; */
        
        if (!V[sp])
        {
            V[sp] = true;
            ++N;
            findNumStates(sp);
        }
    }
}

int main()
{
    int T = 0; // num test cases

    cin >> T;
    
    for (int t = 1; t <= T; ++t)
    {
        // Parse input
        bool aseen = false, bseen = false, cseen = false, dseen = false;
        int x[4], y[4];
        char c;
    
        horizBoard.clear();
        vertBoard.clear();
    
        for (int j = 0; j < 8; ++j)
        {
            for (int i = 0; i < 8; ++i)
            {
                cin >> c;
                
                if (c == '#')
                {
                    horizBoard.push_back(make_pair(i, j));
                    vertBoard.push_back(make_pair(i, j));
                }
                else if (c == 'A' && !aseen)
                {
                    x[0] = i;
                    y[0] = j;
                    //cout << "A" << x[0] << " " << y[0] << endl;
                    aseen = true;
                }
                else if (c == 'B' && !bseen)
                {
                    x[1] = i;
                    y[1] = j;
                    //cout << "B" << x[1] << " " << y[1] << endl;
                    bseen = true;
                }
                else if (c == 'C' && !cseen)
                {
                    x[2] = i;
                    y[2] = j;
                    //cout << "C" << x[2] << " " << y[2] << endl;
                    cseen = true;
                }
                else if (c == 'D' && !dseen)
                {
                    x[3] = i;
                    y[3] = j;
                    //cout << "D" << x[3] << " " << y[3] << endl;
                    dseen = true;
                }
            }
        }
    
        // Initialize variables
        N = 0;

        for (int i = 0; i < MAX_STATE; ++i)
        {
            V[i] = false;
        }

        // Sort blocks
        sort(horizBoard.begin(), horizBoard.end());
        sort(vertBoard.begin(), vertBoard.end(), sort_pred);

        /*
        for (int i = 0; i < horizBoard.size(); ++i)
        {
            cout << "(" << horizBoard[i].first << "," << horizBoard[i].second << ")\n";
        }
cout << "\n";
        for (int i = 0; i < vertBoard.size(); ++i)
        {
            cout << "(" << vertBoard[i].first << "," << vertBoard[i].second << ")\n";
        }
        */

        // Work!
        State cState = coordsToState(x, y);
        findNumStates(cState);

        // Output
        cout << "Case " << t << ": " << N << "\n";
    }

    return 0;
}

/* void print_state(Board &b, State s) {
    int x[4], y[4];
    stateToCoords(x, y, s);
    for(int j=0; j<8; j++) {
        for(int i=0; i<8; i++) {
            if(find(b.begin(), b.end(), MP(i, j)) != b.end()) {
                cout << "#";
                continue;
            }
            int k;
            for(k=0; k<4; k++) {
                if((i == x[k] || i == x[k] + 1) && (j == y[k] || j == y[k] + 1)) {
                    cout << (char)('A' + k);
                    break;
                }
            }
            if(k==4)
                cout << ".";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    Board b;
    State s;
    int x[4] = {0, 5, 2, 6};
    int y[4] = {6, 4, 3, 1};

    for(int j=0; j<8; j++)
        for(int i=0; i<8; i++) {
            int k;
            for(k=0; k<4; k++)
                if((i == x[k] || i == x[k] + 1) && (j == y[k] || j == y[k] + 1))
                    break; 
            if(k == 4 && ! ((i+j) % 3))
                b.PB(MP(i, j));
        }
    s = coordsToState(x, y);
    print_state(b, s);
    Board horizBoard(b);
    Board vertBoard(b);
    sort(horizBoard.begin(), horizBoard.end());
    sort(vertBoard.begin(), vertBoard.end(), sort_pred);
    for(int i=0; i<4; i++)
        print_state(b, transition(i == 1 || i == 2 ? horizBoard : vertBoard , s, (Gravity)i));
    return 0;
} */
