#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int Q[9]; // queen columns
int NT = 0; // do not touch column
int S = 1;

bool collides(int r, int c)
{
    if (r == Q[NT] || abs(NT-c) == abs(Q[NT] - r))
        return true;

    for (int i = 1; i < c; ++i)
    {
        if (Q[i] == r || abs(i - c) == abs(Q[i] - r))
        {
            return true;
        }
    }

    return false;
}

void f(int c)
{
    if (c == 9)
    {
        cout << setw(2) << S++ << "      ";
        
        for (int i = 1; i <= 8; ++i)
        {
            cout << Q[i];

            if (i != 8)
                cout << " ";
        }
        cout << "\n";
    }
    else
    {
        if (c == NT)
        {
            f(c + 1);
        }
        else
        {
            for (int i = 1; i <= 8; ++i)
            {
                if (!collides(i, c))
                {
                    Q[c] = i;
                    f(c + 1);
                }
            }
        }
    }
}

int main()
{
    int N, x, y;
    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        cin >> x >> y;
        NT = y;
        Q[y] = x;
        S = 1;

        cout << "SOLN       COLUMN\n #      1 2 3 4 5 6 7 8\n\n";
        f(1);
    
        if (i != N - 1)
            cout << "\n";
    }

    return 0;
}

