#include<stdio.h>
#include<string.h>

#define N_CHARS ('z' - 'a' + 1)
#define MAX_LEN 1020
#define MAX_RULES 50
#define true 1
#define false 0
typedef char bool;

int rules[3][MAX_RULES], nrules;

struct {
	char t;
	int nt;
} nonterminals[MAX_RULES];
int n_nt;

int len;

bool parsed[N_CHARS][MAX_LEN][MAX_LEN];

char buf1[MAX_LEN], buf2[MAX_LEN];

#define IDX(a, b, c) (((c) * len + (b)) * N_CHARS + (a))

/* credits to Salvador Roura for (showing me?) this pruning implementation of CYK */
bool mark(int c, int e, int d) {
	if(parsed[c][e][d])
		return false;
	if(c == 'S'-'A' && e == 0 && d == len-1)
		return true;
	parsed[c][e][d] = true;
	int i;
	for(i=0; i<nrules; i++) {
		if (c == rules[1][i]) {
			int k, j = rules[2][i], d_1 = d+1;
			for(k = d_1; k < len; k++)
				if(parsed[j][d_1][k] && mark(rules[0][i], e, k))
					return true;
		}
		if (c == rules[2][i]) {
			int k, j = rules[1][i], e_1 = e-1;
			for(k = e_1; k >= 0; k--)
				if(parsed[j][k][e_1] && mark(rules[0][i], k, d))
					return true;
		}
	}
	return false;
}

int main() {
	char *str, *rule, *aux;

	str = buf1;
	rule = buf2;
	scanf("%s", str);

	bool first = true;
	while(str[0]) {
		nrules=0;
		n_nt = 0;
		for(;;) {
			if(scanf("%s", rule) != 1)
				rule[0] = '\0';
			if(rule[0] >= 'a' || !rule[0])
				break;
			if(rule[1] >= 'a') {
				nonterminals[n_nt].t = rule[1];
				nonterminals[n_nt].nt = rule[0] - 'A';
				n_nt++;
			} else {
				rules[0][nrules] = rule[0]-'A';
				rules[1][nrules] = rule[1]-'A';
				rules[2][nrules] = rule[2]-'A';
				nrules++;
			}
		}

		len = strlen(str);
		if(first) {
			first = false;
		} else {
			memset(parsed, 0, sizeof(parsed));
		}

		int j;
		for(j=0; j<n_nt; j++) {
			int i;
			for(i=0; i<len; i++) {
				if(str[i] == nonterminals[j].t && mark(nonterminals[j].nt, i, i)) {
					putchar('1');
					goto finish;
				}
			}
		}
		putchar('0');
finish:
		putchar('\n');

		aux = str;
		str = rule;
		rule = aux;
	}
	return 0;
}
