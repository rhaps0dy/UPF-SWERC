#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    long long n, i;

    for(i=0; i<1000000000000000; i++) {
	n = i * (i+1);
	if(n&1) continue;
	double a = sqrt(n/2);
	if(a == floor(a))
	    cout << n << endl;
    }
    return 0;
}
