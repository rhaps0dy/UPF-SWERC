#include <iostream>
#include <utility>
#include <string>
#include <cstring>

using namespace std;

#define MODULO 10007

int matrix[15][15];

// Returns whether that number is odd or not, and its division by two
pair<bool, string>
divide_by_two(string n) {
    int size = n.size();
    bool is_odd = (n[size-1] & 1) == 1;
    // now divide. If last number is odd, it's as if we subtract 1
    n[size-1] = n[size-1] >> 1;
    for(int i=size-2; i>0; i--) {
	char c = n[i];
	if(c&1)
	    n[i+1] += 5;
	n[i] = c >> 1;
    }
    if(n[0] == '0')
	return make_pair(is_odd, n.substr(1));
    return make_pair(is_odd, n);
}

static void
exponentiate(int m[15][15], string exponent) {
    int m2[15][15], m3[15][15];
    if(exponent.size() == 1 && exponent[0] == 1)
	return;
    memcpy(m2, m, 15*15*sizeof(int));

    pair<bool, string> exp_new = divide_by_two(exponent);
    exponentiate(m, exp_new.second);

    memset(m3, 0, 15*15*sizeof(int));
    for(int i=0; i<15; i++)
	for(int j=0; j<15; j++)
	    for(int k=0; k<15; k++)
		m3[i][j] = (m3[i][j] + m[i][k] * m[k][j]) % MODULO;

    if(exp_new.first) {
	memset(m, 0, 15*15*sizeof(int));
	for(int i=0; i<15; i++)
	    for(int j=0; j<15; j++)
		for(int k=0; k<15; k++)
		    m[i][j] = (m[i][j] + m2[i][k] * m3[k][j]) % MODULO;
    } else {
	memcpy(m, m3, 15*15*sizeof(int));
    }
}

int
main() {
    string planets;
    int Nships;

    cin >> planets;
    for(int i=0; i<planets.size(); i++)
	planets[i] -= '0';
	
    cin >> Nships;
    while(Nships--) {
	int capacity;
	cin >> capacity;
	// add 1 to the number of ships from each distance it adds
	matrix[0][capacity - 1]++;
    }
    // every city is moved downward 1 spot
    for(int i=1; i<15; i++)
	matrix[i][i-1] = 1;

    exponentiate(matrix, planets);
    
    // the initial vector is {1, 0, 0, ... 0}
    cout << matrix[0][0] << endl;
    
    return 0;
}
