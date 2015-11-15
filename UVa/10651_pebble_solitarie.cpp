#include <cmath>
#include <iostream>

using namespace std;

int f(std::string& s, int n)
{
    std::string b =  s;

    int m = n;

    for (int i = 0; i < s.length() - 2; ++i)
    {
        if (s[i] == 'o' && s[i+1] == 'o' && s[i+2] == '-')
        {
            std::string b = s;
            b[i] = '-';
            b[i+1] = '-';
            b[i+2] = 'o';
            
            m = std::min(f(b, n - 1), m);
        }
        else if (s[i] == '-' && s[i+1] == 'o' && s[i+2] == 'o')
        {
            std::string b = s;
            b[i] = 'o';
            b[i+1] = '-';
            b[i+2] = '-';

            m = std::min(f(b, n - 1), m);
        }
    }

    return m;
}

int main()
{
    int N;
    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        char c;        
        std::string s = "";
        int n = 0;

        for (int j = 0; j < 12; ++j)
        {
            cin >> c;

            if (c == 'o') ++n;

            s += c;
        }
    
        cout << f(s, n) << "\n";
    }

    return 0;
}

