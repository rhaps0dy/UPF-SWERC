#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int ab, ac, bd;
    
    while (cin >> ab >> ac >> bd)
    {
        // Tales theorem
        int num = ab * ac;
        int den = bd - ac;
        
        int g = __gcd(num, den);
        
        num /= g;
        den /= g;
        
        cout << num << "/" << den << endl;
    }
    
    return 0;
}

