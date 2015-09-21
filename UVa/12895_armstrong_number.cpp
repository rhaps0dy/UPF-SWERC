#include <iostream>
#include <cmath>

using namespace std;

int D[11]; // decomposed number

bool isArmstrong(int n, int numDigits)
{
    int sum = 0;
    
    for (int i = 0; i < numDigits; ++i)
    {
        sum += pow(D[i], numDigits);
    }
    
    return sum == n;
}

int decompose(int n)
{
    int c = n;

    int numDigits = 0;
    
    while (c != 0)
    {
        int r = c % 10;
        c = c / 10;
        
        D[numDigits] = r;
    
        ++numDigits;
    }
    
    return numDigits;
}

int main()
{
    int T;
    cin >> T;

    int n;

    for (int i = 0; i < T; ++i)
    {
        cin >> n;
        
        int numDigits = decompose(n);
        
        if (isArmstrong(n, numDigits))
        {
            cout << "Armstrong\n";
        }
        else
        {
            cout << "Not Armstrong\n";
        }
    }

    return 0;
}

