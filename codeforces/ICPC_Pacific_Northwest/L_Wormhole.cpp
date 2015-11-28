#include<bits/stdc++.h>

using namespace std;

typedef long long LI;

LI xs[60], ys[60], zs[60];
double adj_mat[60][60];

int main() {
	int kase, ncases;
	cin >> ncases;
	for(kase=1; kase<=ncases; kase++) {
		map<string, int> planets;
		int P;
		cin >> P;
		for(int i=0; i<P; i++) {
			string name;
			int x, y, z;
			cin >> name >> xs[i] >> ys[i] >> zs[i];
			planets[name] = i;
		}
		for(int i=0; i<P; i++) {
			adj_mat[i][i] = 0;
			for(int j=0; j<P; j++) {
				if(j==i) continue;
				LI x=xs[j]-xs[i], y=ys[j]-ys[i], z=zs[j]-zs[i];
				adj_mat[i][j] = sqrt((double)(x*x+y*y+z*z));
			}
		}
		int w;
		cin >> w;
		while(w--) {
			string s1, s2;
			cin >> s1 >> s2;
			adj_mat[planets[s1]][planets[s2]] = 0.0;
		}
			
		for (int k = 0; k < P; k++)
			for (int i = 0; i < P; i++)
				for (int j = 0; j < P; j++)
					adj_mat[i][j] = min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);

		printf("Case %d:\n", kase);
		int q;
		cin >> q;
		while(q--) {
			string s1, s2;
			cin >> s1 >> s2;
			LI d = round(adj_mat[planets[s1]][planets[s2]]);
			cout << "The distance from " << s1 << " to " << s2 << " is " << d <<
				" parsecs." << endl;
		}
	}
	return 0;
}
