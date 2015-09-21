#include <iostream>
#include <vector>

using namespace std;

vector<int> primes;

bool sieve[10001];

int
main()
{
    for(int i=2; i<=10000; i++) {
        if(!sieve[i]) {
            primes.push_back(i);
            for(int j=2; i*j<=10000; j++)
                sieve[i*j] = true;
        }
    }

    int N, prec, mrec, n, m, p;
    cin >> N;
    for(; N>0; N--) {
        cin >> n;
        mrec = 99999999;
//        cout << "For number " << n << endl;
        for(int i=0; i<(int)primes.size() && primes[i] <= n; i++) {
            p = n / primes[i];
//            cout << "p = " << p << "; primes[i] = " << primes[i] << "; m = " << m << ";\n";
            m = p*primes[i];
            if(m < mrec) {
                mrec = m;
                prec = primes[i];
            }
        }
        cout << prec << endl;
    }

    return 0;
}
