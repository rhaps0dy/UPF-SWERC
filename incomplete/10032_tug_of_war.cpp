#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

static int
getLineNumber() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int n;
    if(ss >> n)
			return n;
    return 0;
}

#define MAX_PEOPLE_MIN_SET (450*100/2)
int g1,g2;
static long long
n_make_weight[MAX_PEOPLE_MIN_SET];

static void
solve(vector<int> &people) {
    memset(n_make_weight, 0, sizeof(n_make_weight));
    int n_people = people.size();
    int sum;
    for(int i=0; i<n_people; i++)
			sum += people[i];
    n_make_weight[0] = 1;
    int sum_2 = sum/2;
    for(int j=0; j<sum_2; j++) {
			for(int i=0; i<n_people; i++) {
					int index = j-people[i];
					if(index >= 0)
				n_make_weight[j] |= n_make_weight[index] << 1;
			}
		}
    for(int i=sum_2-1; i>0; i--) {
			if(n_make_weight[i] | (0x3 << (n_people/2 - 1))) {
				g1 = i ;
				g2 = sum - i ;
			}
    }
}

int main() {
    int Ncases = getLineNumber();
    vector<int> people;
    people.reserve(100);
    getLineNumber();
    while(Ncases--) {
			int w;
			people.clear();
			while((w=getLineNumber()))
					people.push_back(w);
			solve(people);
			cout<<g1<<" "<<g2<<endl;
			
		}
    return 0;
}
