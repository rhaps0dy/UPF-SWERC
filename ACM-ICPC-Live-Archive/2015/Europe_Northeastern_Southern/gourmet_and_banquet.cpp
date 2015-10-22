// http://codeforces.com/problemset/problem/589/F

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

typedef pair<int, int> Dish;

bool isValidAssignment(const vector<Dish>& dishes, int t, int latest)
{
    // Array containing the time that a dish has been eaten
    int T[101];
    fill(T, T + 101, 0);

    for (int i = 0; i <= latest; ++i)
    {
        // best dish to whom time will be assinged
        int bestDish = -1;
    
        for (int j = 0; j < dishes.size(); ++j)
        {
            const Dish& dish = dishes[j];
            
            // if the time to eat a dish has finished and
            // there is not more time --> no assignment possible
            if (dish.second == i && T[j] < t)
            {
                return false;
            }
            
            bool insideInterval = dish.first <= i && i < dish.second;
            bool timeNotComplete = T[j] < t;
            bool isBestDish = bestDish == -1 || 
                              dishes[bestDish].second > dishes[j].second;
            
            if (insideInterval && timeNotComplete && isBestDish)
            {
                bestDish = j;
            }
        }
        
        ++T[bestDish];
    }
    
    return true;
}

int main()
{
    int N; // number of dishes

    while (cin >> N)
    {
        vector<Dish> dishes(N);
    
        int latest = -1;
        
        // No dish can be eaten during more time than the dish
        // which has less time to be eaten
        int minTime = 10001;
    
        for (int i = 0; i < N; ++i)
        {
            cin >> dishes[i].first >> dishes[i].second;
            
            int diff = dishes[i].second - dishes[i].first;            
            minTime = min(minTime, diff);
            latest = max(latest, dishes[i].second);
        }
        
        // Binary search for the different possible times that a dish
        // can be eaten
        int tlow = 0;
        int thigh = minTime;
        
        while (tlow < thigh)
        {
            int tmid = (thigh + tlow + 1) / 2;
            
            if (isValidAssignment(dishes, tmid, latest))
            {
                tlow = tmid;
            }
            else
            {
                thigh = tmid - 1;
            }
        }
        
        cout << N * tlow << endl;
    }

    return 0;
}

