#include <iostream>
#include <sstream>

using namespace std;

char K[][4] = {{' ', '_', '_', '_' },
               {'.', ',', '?', '\"'},
               {'a', 'b', 'c', '_' },
               {'d', 'e', 'f', '_' },
               {'g', 'h', 'i', '_' },
               {'j', 'k', 'l', '_' },
               {'m', 'n', 'o', '_' },
               {'p', 'q', 'r', 's' },
               {'t', 'u', 'v', '_' },
               {'w', 'x', 'y', 'z' }};

int N[] = {1, 4, 3, 3, 3, 3, 3, 4, 3, 4};

int L = 0; // length of the message
int M[101]; // message
int R[101]; // repetitions

char getChar(int num, int times)
{
    return K[num][(times - 1) % N[num]];
}

int main()
{
    int T = 0;
    cin >> T;

    for (int i = 0; i < T; ++i)
    {
        cin >> L;
        
        for (int j = 0; j < L; ++j)
        {
            cin >> M[j];
        }
        
        for (int j = 0; j < L; ++j)
        {
            cin >> R[j];
        }
        
        stringstream ss;
        
        for (int j = 0; j < L; ++j)
        {
            ss << getChar(M[j], R[j]);
        }
        
        cout << ss.str() << endl;
    }

    return 0;
}

