#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> combinations;

void dfs(const vector<vector<int> > &adj, int n, int depth) {
	int nn = n % 10;
	for(int i=0; i<adj[nn].size(); i++) {
		int nnn = n * 10 + adj[nn][i];
		combinations.push_back(nnn);
		if(depth != 3)
			dfs(adj, nnn, depth+1);
	}
}

int main() {
	vector<vector<int> > adj(10);
	for(int i=1; i<10; i++) {
		for(int j=i+1; j<10; j++) {
			if((j-1) % 3 >= (i-1) % 3)
				adj[i].push_back(j);
		}
		if((i-1)%3 != 2)
			adj[i].push_back(0);
		adj[i].push_back(i);
	}
	adj[0].push_back(0);

	for(int i=0; i<10; i++) {
		combinations.push_back(i);
		dfs(adj, i, 2);
	}

/*	for(set<int>::iterator it = combinations.begin(); it != combinations.end(); it++)
		cout << *it << endl; */

	sort(combinations.begin(), combinations.end());

	int Ncases;
	cin >> Ncases;
	while(Ncases--) {
		int n;
		cin >> n;

		auto it = lower_bound(combinations.begin(), combinations.end(), n);
		if(n == *it) {
			cout << n << endl;
			continue;
		}
		int a = *it, c = *(it-1);
		if(n-c < a-n)
			cout << c << endl;
		else
			cout << a << endl;
	}
	return 0;
}
