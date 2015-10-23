#include<iostream>
#include<string>
#include<cstdio>
#include<stack>
#include<utility>

#define MAX 81

using namespace std;

enum Op {
	NOTHING,
	INSERT,
	DELETE,
	REPLACE
} ops[MAX][MAX];
int cost[MAX][MAX];

string s1, s2;

int main() {
	for(int i=0; i<MAX; i++)
		cost[0][i] = cost[i][0] = i;

	bool not_first = false;
	while(getline(cin, s1) && getline(cin, s2)) {
		if(not_first)
			putchar('\n');
		else
			not_first = true;
		int s1_len = s1.size(), s2_len = s2.size();
		for(int j=1; j<=s2_len; j++) {
			for(int i=1; i<=s1_len; i++) {
				int a = cost[j][i-1] + 1;
				int b = cost[j-1][i] + 1;
				int c = cost[j-1][i-1];
				Op opc;
				if(s2[j-1] == s1[i-1]) {
					opc = NOTHING;
				} else {
					c++;
					opc = REPLACE;
				}
				if(a < b && a < c) {
					cost[j][i] = a;
					ops[j][i] = DELETE;
				} else if(b < c) {
					cost[j][i] = b;
					ops[j][i] = INSERT;
				} else {
					cost[j][i] = c;
					ops[j][i] = opc;
				}
			}
		}
		printf("%d\n", cost[s2_len][s1_len]);

		int i = s1_len, j = s2_len;
		stack<pair<Op, pair<int, char> > > actions;
		while(i != 0 && j != 0) {
			switch(ops[j][i]) {
			case REPLACE:
				actions.push(make_pair(REPLACE, make_pair(i, s2[j-1])));
			case NOTHING:
				i--; j--;
				break;
			case INSERT:
				actions.push(make_pair(INSERT, make_pair(i+1, s2[j-1])));
				j--;
				break;
			case DELETE:
				actions.push(make_pair(DELETE, make_pair(i, '?')));
				i--;
				break;
			}
		}
		for(; i>0; i--)
			actions.push(make_pair(DELETE, make_pair(i, '?')));
		for(; j>0; j--)
			actions.push(make_pair(INSERT, make_pair(1, s2[j-1])));
		int pos_offset=0, index=1;
		while(!actions.empty()) {
			pair<Op, pair<int, char> > &p = actions.top();
			switch(p.first) {
			case REPLACE:
				printf("%d Replace %d,%c\n", index, p.second.first + pos_offset, p.second.second);
				break;
			case INSERT:
				printf("%d Insert %d,%c\n", index, p.second.first + pos_offset, p.second.second);
				pos_offset++;
				break;
			case DELETE:
				printf("%d Delete %d\n", index, p.second.first + pos_offset);
				pos_offset--;
				break;
			case NOTHING: break;
			}
			actions.pop();
			index++;
		}
		#ifndef ONLINE_JUDGE
		for(j=0; j<=s2_len; j++) {
			for(i=0; i<=s1_len; i++) {
				switch(ops[j][i]) {
				case REPLACE: printf("Rpl "); break;
				case NOTHING: printf(" -  "); break;
				case INSERT: printf("Ins "); break;
				case DELETE: printf("Del "); break;
				}
			}
			putchar('\n');
		}
		#endif
	}
	return 0;
}
