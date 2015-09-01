// This code performs maximum bipartite matching.
// https://web.stanford.edu/~liszt90/acm/notebook.html#file5
//
// Running time: O(|E| |V|) -- often much faster in practice
//
// INPUT: w[i][j] = edge between row node i and column node j
// OUTPUT: mr[i] = assignment for row node i, -1 if unassigned
//         mc[j] = assignment for column node j, -1 if unassigned
//         function returns number of matches made

#include <iostream>
#include <vector>

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

int main()
{
    int N, M;

    while (cin >> N >> M)
    {
        int a, b;
    
        VVI w;
        VI mr;
        VI mc;
    
        w.resize(N);
    
        for (int i = 0; i < N; ++i)
        {
            w[i].resize(N);
            
            for (int j = 0; j < N; ++j)
            {
                w[i][j] = 0;
            }
        }
    
        for (int i = 0; i < M; ++i)
        {
            cin >> a >> b;
            w[a][b] = 1;
        }
        
        int numMatches = BipartiteMatching(w, mr, mc);
        
        if (numMatches == N)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }

    return 0;
}

