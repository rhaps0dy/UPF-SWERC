#include <iostream>
#include <set>
#include <climits>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long int LI;

LI gcd(LI a, LI b) {
    if(a < b) return gcd(b, a);
    if(a % b == 0) return b;
    return gcd(b, a%b);
}

int N, S, T;

LI fun(multiset<int> bags, int s) {

//        cout << "bags: ";         for(auto iii = bags.begin(); iii != bags.end(); iii++) {         cout << *iii << " ";      }         cout << endl;

//cout << "Empezando bolsa " << s;
    bags.erase(bags.lower_bound(s));
    s = (s + T) % S;
    LI res = N * T;
 //   cout << " res = " << res;
    do {

        if(bags.lower_bound(s) == bags.end()) {
            res += S - s;
            s = 0;
        }
        multiset<int>::iterator bb = bags.lower_bound(s);
        int b = *bb;
        res += b-s;
        s = (b + T) % S;

//        cout << "b = " << b << " res = " << res << endl;

        bags.erase(bb);
    } while(!bags.empty());
    return res;
}

int main() {
        multiset<int> bags;
    while(cin >> N >> S >> T) {

        bags.clear();
        for(int i=0; i<N; i++) {
            int n;
            cin >> n;
            bags.insert(n);
        }

        int prev_e = *bags.rbegin() - S;
        LI max_res = LLONG_MIN, min_res = LLONG_MAX;
        LI sum = 0;
        for(auto it = bags.begin(); it != bags.end(); it++) {
            int e = *it;
            LI res = fun(bags, e);

            int n_tries = e - prev_e - 1;
            max_res = max(res + n_tries, max_res);
            min_res = min(res, min_res);

            res *= n_tries + 1;
            if(n_tries > 0) {
                res += n_tries * (n_tries + 1) / 2;
            }

            sum += res;
            prev_e = e;
        }

        LI nn = (LI) S;
        LI g = gcd(sum, nn);
        sum /= g;
        nn /= g;
        cout << min_res << endl;
        cout << max_res << endl;
        if(nn == 1) {
            cout << sum << endl;
        } else {
            cout << sum << "/" << nn << endl;
        }
    }
    return 0;
}
