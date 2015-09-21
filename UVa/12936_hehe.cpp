#include <iostream>
#include <string>
#include <utility>
#include <iomanip>
#include <map>

using namespace std;

#define is_alphabetic(c) ((((c) >= 'a') && ((c) <= 'z')) || (((c) >= 'A') && ((c) <= 'Z')))

static bool
line_contains_hehe(const string &line, int i) {
    int sz = line.size();
    int j;
    while(i<sz) {
        for(; i<sz && !is_alphabetic(line[i]); i++);
        bool isHehe = true;
        for(j=0; j+i<sz && is_alphabetic(line[j+i]); j++) {
            char c = line[j+i];
            if(j&1) {
                isHehe = isHehe && (c == 'e' || c == 'E');
            } else {
                isHehe = isHehe && (c == 'h' || c == 'H');
            }
        }
        if(isHehe && j >= 4) return true;
        i += j;
    }
    return false;
}

#undef is_alphabetic

int main() {
    string line;
    line.reserve(1000);
    map<pair<string, string>, bool> conversations;
    while(true) {
        getline(cin, line);
        int sz;
        if((sz=line.size()) == 0)
            break;
        int arrow = line.find("->");
        string a = line.substr(0, arrow);
        int colon = line.find(":");
        string b = line.substr(arrow+2, colon-arrow-2);
        pair<string,string> idx;
        idx = (a < b ? make_pair(a, b) : make_pair(b, a));
        conversations[idx] = line_contains_hehe(line, colon+1);
    }
    int consz;
    if((consz=conversations.size()) == 0) {
        cout << "0%" << endl;
    } else {
        int heheLines = 0;
        for(auto it=conversations.begin(); it != conversations.end(); it++)
            heheLines += (it->second ? 1 : 0);
        cout << fixed << setprecision(0);
        cout << ((double)heheLines * 100)/((double)consz) << '%' << endl;
    }
    return 0;
}
