#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct SuffixArray {
	const int L;
	string s;
	vector<vector<int> > P;
	vector<pair<pair<int, int>, int> > M;

	SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L) {
		for (int i = 0; i < L; i++) P[0][i] = int(s[i]);
		for (int skip = 1, level = 1; skip < L; skip *= 2, level++) {
			P.push_back(vector<int>(L, 0));
			for (int i = 0; i < L; i++)
				M[i] = make_pair(make_pair(P[level - 1][i], i + skip < L ? P[level - 1][i + skip] : -1000), i);
			sort(M.begin(), M.end());
			for (int i = 0; i < L; i++)
				P[level][M[i].second] = (i > 0 && M[i].first == M[i - 1].first) ? P[level][M[i - 1].second] : i;
		}
	}

	vector<int> GetSuffixArray() { return P.back(); }

	// returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
	int LongestCommonPrefix(int i, int j) {
		int len = 0;
		if (i == j) return L - i;
		for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
			if (P[k][i] == P[k][j]) {
				i += 1 << k;
				j += 1 << k;
				len += 1 << k;
			}
		}
		return len;
	}
};

int main()
{
	// Compile with C++11
	// http://stanford.edu/~liszt90/acm/notebook.html

	int S[40001]; // Array with max size of the string; suffixes indices are saved here
	int N = 0; // Actual size of the string
	int M = 0; // Minimum number of repetions
	string W; // The string to be analyzed

	while (1)
	{
		cin >> M;

		if (M == 0) break;

		cin >> W;

		N = W.size();

		SuffixArray suffix(W);
		vector<int> v = suffix.GetSuffixArray();

		// Suffix array is not given in the format we need
		// We need just the inverse sense of the data
		for (int i = 0; i < N; ++i)
		{
			S[v[i]] = i;
		}

		// Max length of a string that appears at least M times
		int maxl = -1;

		// Max right position of a string that appears at least M times
		// i.e. the suffix with the biggest index of appearance that contains the indicated string
		int maxr = -1;

		for (int i = 0; i <= N - M; ++i)
		{
			// We just need compare suffix at 'i' with suffix at 'i + M - 1'
			// since that if S[i + M - 1] contains a shared prefix with S[i],
			// then all other will contain it
			// If S[i + M - 1] does not contain a shared prefix, then we will
			// not have at least M equal prefixes
			int s1 = S[i];
			int s2 = S[i + M - 1];

			int length = suffix.LongestCommonPrefix(s1, s2);

			if (length > maxl)
			{
				maxl = length;

				// Set max right position which corresponds to the suffix between
				// S[i] and S[i + M - 1] included, that has a higher index.
				maxr = *max_element(S + i, S + i + M);
			}
			else if (length == maxl) // we can have equal length but the index can be at a 'more' right position!
			{
				maxr = max(maxr, *max_element(S + i, S + i + M));
			}
		}

		if (maxl <= 0)
		{
			cout << "none" << endl;
		}
		else
		{
			cout << maxl << " " << maxr << endl;
		}
	}

	return 0;
}
