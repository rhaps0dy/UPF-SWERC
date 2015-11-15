#include <iostream>

using namespace std;

int num[17];

int N, H, D;

void f(int i, int n)
{
    if (i != N)
    {
        // 0
        num[i] = 0;
        f(i + 1, n);

        // 1
        if (n < H)
        {
            num[i] = 1;
            f(i + 1, n + 1);
        }
    }
    else
    {
        if (n == H)
        {
            for (int j = 0; j < N; ++j)
            {
                cout << num[j];
            }

            cout << endl;
        }
    }
}

int main()
{
    cin >> D;

    for (int i = 0; i < D; ++i)
    {
        cin >> N >> H;
        f(0,0);

        if (i != D-1)
            cout << endl;
    }

    return 0;
}

