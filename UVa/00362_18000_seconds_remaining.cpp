#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int S = 0;
    int C = 1;

    while (cin >> S)
    {
        if (S == 0)
        {
            break;
        }

        cout << "Output for data set " << C << ", " << S << " bytes:\n";

        int sum = 0;
        int c = 0;
        int r = 0;
        int T = 0;

        while (cin >> r)
        {
            ++T;
            sum += r;
            ++c;
            S -= r;

            if (c == 5)
            {
                cout << "   Time remaining: ";

                if (sum == 0)
                {
                    cout << "stalled";
                }
                else
                {
                    int remSec = ceil(double(S * 5) / double(sum));
                    cout << remSec << " seconds";
                }

                sum = c = 0;
                cout << "\n";
            }

            if (S == 0)
            {
                break;
            }
        }
    
        cout << "Total time: " << T << " seconds\n\n";
        ++C;
    }

    return 0;
}

