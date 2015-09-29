#include <cstdio>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

#define MAX_PEOPLE_MIN_SET (450*100/2)
int g1,g2;

static long long
n_make_weight[MAX_PEOPLE_MIN_SET];

static void
solve(vector<int> &people) {
	memset(n_make_weight, 0, MAX_PEOPLE_MIN_SET*sizeof(long long));
	int n_people = people.size();
	int sum = 0;
	for(int i=0; i<n_people; i++)
		sum += people[i];

	n_make_weight[0] = 1;
	int sum_2 = sum/2;
	for(int i=0; i<n_people; i++)
		for(int j=sum_2; j>=people[i]; j--)
			n_make_weight[j] |= n_make_weight[j-people[i]] << 1;


	long long mask_to_test;
	if(n_people%2)
		mask_to_test = 0x3;
	else
		mask_to_test = 0x1;
	mask_to_test <<= n_people/2;

	for(int i=sum_2; i>=0; i--) {
		if(n_make_weight[i] & mask_to_test) {
			g1 = i;
			g2 = sum - i;
			return;
		}
	}
}

int main() {
	int Ncases;
	vector<int> people;
	people.reserve(100);

	scanf("%d", &Ncases);
	while(Ncases--) {
		int n, w;
		scanf("%d", &n);
		people.clear();
		while(n--) {
			scanf("%d", &w);
			people.push_back(w);
		}
		solve(people);
		printf("%d %d\n", g1, g2);
		if(Ncases)
			putchar('\n');
	}
	return 0;
}
