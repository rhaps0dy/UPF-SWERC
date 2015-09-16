#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

map<string, int> species;

int main() {
    int Ncases;
    string name;
    cin >> Ncases;
    getline(cin, name);
    getline(cin, name);
    for(int ncase=0; ncase<Ncases; ncase++) {
        species.clear();
        int Nspecies = 0;
        while(getline(cin, name) && name.size() > 0) {
            if(species.find(name) == species.end())
                species[name] = 1;
            else
                species[name]++;
            Nspecies++;
        }
        cout << setprecision(4) << fixed;
        for(auto it=species.begin(); it != species.end(); it++) {
            cout << it->first << " " << (((double)it->second) / ((double) Nspecies) * 100.) << endl;
        }
        if(ncase != Ncases-1)
            cout << endl;
    }
    return 0;
}
