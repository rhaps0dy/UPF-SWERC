#include <iostream>
#include <cmath>

#define DEG_BET_HOUR 30.0
#define DEG_BET_MIN 6.0
#define HOUR_DEG_PER_MIN 0.5

using namespace std;

int main()
{
    double hour = 0.0, min = 0.0;
    char inv = ' ';
    
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(3);
    
    while (1)
    {
          cin >> hour >> inv >> min;
          
          if ((hour == 0) && (min == 0))
             break;
             
          double hourDeg = fmod(hour, 12) * DEG_BET_HOUR + min * HOUR_DEG_PER_MIN;
          double minDeg = min * DEG_BET_MIN;
          double defDif = abs(hourDeg - minDeg);
          
          if (defDif > 180.0)
             defDif = 360.0 - defDif;
          
          cout << defDif << endl;
    }

    return 0;
}
