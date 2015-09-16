#include <iostream>

using namespace std;

bool isValid(double x0, double x1, double y0, double y1, double cx, double cy, double r)
{
    double l = x1 - x0;
    double w = y1 - y0;
    
    // Check length-width proportion
    if (w != (l * 0.6)) return false;

    // Check radius size
    if (l != (r * 5.0)) return false;
    
    // Check circle center cx
    if ((cx - x0) != (l * 9.0 / 20.0)) return false;
    
    // Check circle center cy
    if (w != (cy - y0) * 2.0) return false;
    
    return true;
}

int main()
{
    int T;
    cin >> T;
    
    double x0, y0, x1, y1, cx, cy, r;
    
    for (int i = 0; i < T; ++i)
    {
        cin >> x0 >> y0 >> x1 >> y1 >> cx >> cy >> r;
        
        if (isValid(x0, x1, y0, y1, cx, cy, r))
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }

    return 0;
}

