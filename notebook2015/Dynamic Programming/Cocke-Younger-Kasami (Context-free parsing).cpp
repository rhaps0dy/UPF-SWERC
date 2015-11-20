// O(n^3 |G|) worst case, bigger constant factor
int rules[3][MAX_RULES], nrules;

struct {
    char t;
    int nt;
} nonterminals[MAX_RULES];
int n_nt;

int len;
bool parsed[N_CHARS][MAX_LEN][MAX_LEN];

bool mark(int c, int e, int d) {
    if(parsed[c][e][d])
        return false;
    if(c == ROOT_NONTERMINAL && e == 0 && d == len-1)
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

scanf("%s", str);
// scan rules
// rules[0][i] := rules[1][i] rules[2][i]

len = strlen(str);
memset(parsed, 0, sizeof(parsed));
int j;
for(j=0; j<n_nonterminals; j++) {
    int i;
    for(i=0; i<len; i++) {
        if(str[i] == nonterminals[j].t && mark(nonterminals[j].nt, i, i)) {
            putchar('1');
            goto finish;
        }
    }
}
putchar('0');
finish: putchar('\n');

// O(n^3 |G|) worst case, smaller constant factor. Can parse n=1000 with about
// 20 rules in less than 5s
for(i=0; i<len; i++) {
    int a = str[i]-'a';
    int b;
    for(b=0; b<N_CHARS; b++)
        parsed[b][i][i] = nonterminals[b][a];
    int j;
    for(j=i-1; j >= 0; j--) {
        int l;
        for(l=0; l<N_CHARS; l++)
            parsed[l][i][j] = false;
        int k;
        for(k=j; k<i; k++) {
            int r;
            for(r=0; r<nrules; r++) {
                if(parsed[rules[1][r]][k][j] && parsed[rules[2][r]][i][k+1])
                    parsed[rules[0][r]][i][j] = true;
            }
        }
    }
}

if(parsed['S'-'A'][len-1][0])
    putchar('1');
else
    putchar('0');
putchar('\n');
