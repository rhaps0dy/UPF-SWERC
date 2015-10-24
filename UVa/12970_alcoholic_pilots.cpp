#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    unsigned long long v1, d1, v2, d2;
    int ncase=0;
    while (cin >> v1 >> d1 >> v2 >> d2)
    {
        if(v1 == 0 && d1 == 0 && v2 == 0 && d2 == 0) break;

        ncase++;

        cout << "Case #" << ncase << ": ";
        
        if(d1 * v2 < d2 * v1)
            cout << "You owe me a beer!\n";
        else
            cout << "No beer for the captain.\n";

        unsigned long long a = d1 * v2 + v1 * d2, b = v1 * v2 * 2;
    
        unsigned long long g = std::__gcd(a, b);
        if(g != 0) {
            a /= g;
            b /= g;
        }

        cout << "Avg. arrival time: ";
        
        if(b == 1)
            cout << a << endl;
        else
            cout << a << "/" << b << endl;
    }
    
    return 0;
}

