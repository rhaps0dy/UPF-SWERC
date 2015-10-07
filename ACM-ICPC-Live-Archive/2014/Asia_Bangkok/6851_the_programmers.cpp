#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

bool FindMatch(int i, const VVI &w, VI &mr, VI &mc, VI &seen) {
  for (int j = 0; j < w[i].size(); j++) {
    if (w[i][j] && !seen[j]) {
      seen[j] = true;
      if (mc[j] < 0 || FindMatch(mc[j], w, mr, mc, seen)) {
        mr[i] = j;
        mc[j] = i;
        return true;
      }
    }
  }
  return false;
}

int BipartiteMatching(const VVI &w, VI &mr, VI &mc) {
  mr = VI(w.size(), -1);
  mc = VI(w[0].size(), -1);
  int ct = 0;
  for (int i = 0; i < w.size(); i++) {
    VI seen(w[0].size());
    if (FindMatch(i, w, mr, mc, seen)) ct++;
  }
  return ct;
}

int main() {
    VI mr, mc;
    VVI w;

    int Ncases;
    cin >> Ncases;
    while(Ncases--) {
	int P, S, C, n_lines;
	cin >> P >> S >> C >> n_lines;

	w.resize(P);
	for(int i=0; i<P; i++) {
	    w[i].clear();
	    w[i].resize(S*C, 0);
	}

	while(n_lines--) {
	    int j, i;
	    scanf("%d %d", &j, &i);
	    for(int k=0; k<C; k++)
		w[j-1][(i-1)*C+k] = 1;
	}

	cout << BipartiteMatching(w, mr, mc) << endl;
    }
    return 0;
}
