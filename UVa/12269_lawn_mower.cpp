#include <iostream>
#include <algorithm>

using namespace std;

double x[1001];
double y[1001];

int main()
{
    int nx, ny;
    double w;

    while (cin >> nx >> ny >> w)
    {
        if (nx == 0 && ny == 0 && w == 0.0) break;

        for (int i = 0; i < nx; ++i) cin >> x[i];
        for (int i = 0; i < ny; ++i) cin >> y[i];
    
        sort(x, x + nx);
        sort(y, y + ny);

        bool okCut = true;
        double lastBound = 0.0;

        for (int i = 0; i < nx; ++i)
        {
            double c = x[i];
            double lc = x[i] - 0.5 * w;
            double uc = x[i] + 0.5 * w;

            if (lc > lastBound)
            {
                okCut = false;
                break;
            }
            else
            {
                if (i == nx - 1)
                {
                    if (uc < 75.0)
                    {
                        okCut = false;
                        break;
                    }
                }
                else
                {
                    lastBound = uc;
                }
            }
        }
        
        if (!okCut)
        {
            cout << "NO" << endl;
            continue;
        }

        lastBound = 0.0;

        for (int i = 0; i < ny; ++i)
        {
            double c = y[i];
            double lc = y[i] - 0.5 * w;
            double uc = y[i] + 0.5 * w;

            if (lc > lastBound)
            {
                okCut = false;
                break;
            }
            else
            {
                if (i == ny - 1)
                {
                    if (uc < 100.0)
                    {
                        okCut = false;
                        break;
                    }
                }
                else
                {
                    lastBound = uc;
                }
            }
        }

        if (!okCut)
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;
        }
    }

    return 0;
}

