#include<bits/stdc++.h>

using namespace std;

typedef long long LI;

char s[300];

#define BAD 0x3f3f3f3f

int read_number(char *s, int &i, int j) {
	int sign = 1;
	if(s[i] == '-') {
		sign = -1;
		i++;
	}
	if(s[i] == '?' && j==0 && ((s[i+1] >= '0' && s[i+1] <= '9') || s[i+1] == '?' || sign == -1))
		return BAD;
	int n=0;
	for(; (s[i] >= '0' && s[i] <= '9') || s[i] == '?'; i++) {
		n *= 10; 
		if(s[i] == '?')
			n += j;
		else
			n += s[i]-'0';
	}
	return n*sign;
}

int main() {
	int ncases;
	while(scanf("%d", &ncases) == 1) {
		while(ncases--) {
			scanf("%s", s);
			int i = 0, j=0;
			for(; j<=9; j++) {
				bool cont=false;
				for(int k=0; s[k]; k++) {
					if(s[k] >= '0' && s[k] <= '9' && s[k] -'0' == j)
						cont=true;
				}
				if(cont) continue;
				i=0;
				LI n1 = read_number(s, i, j);
				char op = s[i++];
				LI n2 = read_number(s, i, j);
				i++;
				LI n3 = read_number(s, i, j);
				if(n1 == BAD || n2==BAD || n3==BAD) continue;
				printf("'%lld' %c '%lld' = '%lld'\n", n1, op, n2, n3);
				switch(op) {
				case '*': if(n1*n2 == n3) goto end; break;
				case '+': if(n1+n2 == n3) goto end; break;
				case '-': if(n1-n2 == n3) goto end; break;
				}
			}
			j = -1;
		end:
			printf("%d\n", j);
		}
	}
	return 0;
}
