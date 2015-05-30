#include <iostream>
#include <string>
#include <cstring>

using namespace std;


int
main()
{
    int N;
    char message[81];
    cin >> N;

    for(; N>0; N--) {
        string s;
        memset(message, 0, 81*sizeof(char));
        cin >> s;
        for(int i=0; i<8; i++) {
            cin >> s;
            for(int j=0; j<s.size()-2; j++) {
                if(s[j+1] == '\\') {
                    message[j] |= 0x01 << i;
                }
            }
        }
        cin >> s;
        cout << message << endl;
    }
}
