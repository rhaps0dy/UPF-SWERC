#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <map>

using namespace std;

#define MAX 160

char mat[MAX][MAX];

typedef unsigned long long Hash;


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
	int Ncases;
	scanf("%d", &Ncases);

	Hash astragalus, garbancillos;
	const Hash gar_keep = 0xfffffffffffffffLL, ast_keep = 0x3ffffffffffffLL;
	const char *ast = "ASTRAGALUS", *gar = "GARBANCILLOS";
	const int ast_len = strlen(ast), gar_len = strlen(gar);
	astragalus=0;
	for(int i=0; ast[i]; i++) {
		astragalus <<= 5;
		astragalus |= ast[i] - 'A';
	}
	garbancillos=0;
	for(int i=0; gar[i]; i++) {
		garbancillos <<= 5;
		garbancillos |= gar[i] - 'A';
	}
	while(Ncases--) {
		int R, C;
		scanf("%d %d", &R, &C);
		gets(&mat[0][0]);
		for(int i=0; i<R; i++)
			gets(&mat[i][0]);
		if(R < ast_len || C < gar_len) {
			puts("0");
			continue;
		}
		vector<int> gar_starts[MAX];

		int garban_n = 0;
		map<int, int> garban_indices;

		int j, i;
		for(j=0; j<R; j++) {
			Hash h = 0;
			for(i=0; i<gar_len-1; i++) {
				h <<= 5;
				h |= (mat[j][i] < 'A' || mat[j][i] > 'Z' ? 0x1f : mat[j][i] - 'A');
			}
			for(; i<C; i++) {
				h = ((h << 5) & gar_keep) | (mat[j][i] < 'A' || mat[j][i] > 'Z' ? 0x1f : mat[j][i] - 'A');
				if(h == garbancillos) {
					gar_starts[j].push_back(i);
					garban_indices[j * MAX + i] = garban_n++;
				}
			}
			gar_starts[j].push_back(MAX + 200); // avoid edge cases later
		}

		VVI used;

		for(i=0; i<C; i++) {
			Hash h = 0;
			for(j=0; j<ast_len-1; j++) {
				h <<= 5;
				h |= (mat[j][i] < 'A' || mat[j][i] > 'Z' ? 0x1f : mat[j][i] - 'A');
			}
			for(; j<R; j++) {
				h = ((h << 5) & ast_keep) | (mat[j][i] < 'A' || mat[j][i] > 'Z' ? 0x1f : mat[j][i] - 'A');
				if(h == astragalus) {
					VI this_astragalus(garban_n, 0);
					for(int k=j-ast_len+1; k<=j; k++) {
						int gst = *lower_bound(gar_starts[k].begin(), gar_starts[k].end(), i);
						if(gst < i+gar_len) {
							this_astragalus[garban_indices[k*MAX + gst]] = 1;
						}
					}
					used.push_back(this_astragalus);
				}
			}
		}
		VI a, b;
		if(used.size() == 0 || used[0].size() == 0) {
			puts("0");
		} else {
			printf("%d\n", BipartiteMatching(used, a, b));
		}
	}
	return 0;
}
