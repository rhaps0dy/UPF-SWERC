#include <iostream>
#include <climits>

using namespace std;

int main()
{
    int Nbach, Nspin;
    int Ncase = 1;
    while(cin >> Nbach >> Nspin) {
        if(Nbach == 0 && Nspin == 0) break;
        int youngest, age;
        youngest = INT_MAX;
        for(int i=0; i<Nbach; i++) {
            cin >> age;
            if(age < youngest)
                youngest = age;
        }
        for(int i=0; i<Nspin; i++)
            cin >> age;

        Nbach -= Nspin;
        if(Nbach < 0)
            Nbach = 0;
        cout << "Case " << Ncase << ": " << Nbach;
        if(Nbach != 0)
            cout << " " << youngest;
        cout << endl;
        Ncase++;
    }
    return 0;
}
