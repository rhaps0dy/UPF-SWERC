#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main()
{
    int n, id, x, y, z;

    bool first = true;

    while(cin >> n) {
vector<pair<int, int> > statues;
        if(!first)
            cout << endl;
        first = false;

        for(; n>0; n--) {
            cin >> id >> x >> y >> z;
            statues.push_back(make_pair(x*y*z, id));
        }

        sort(statues.begin(), statues.end());

        for(int i=0; i< statues.size(); i++)
            cout << statues[i].second << endl;
    }

    return 0;
}

