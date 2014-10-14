#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD_VAL 21092013
#define MAX_LEN 100001

typedef long N;

/* stores value of next L and R postfix to a U letter */
typedef struct UEntry UEntry;
struct UEntry {
	N l, r;
};

/* Processes the initial instruction string, outputting an LR-only string of moves
actually made and returning the tree level. Assumes s ends in nullchar */
static N
process_insts(char *lrs, char *s)
{
	N level;

	level=0;
	for(; *s; s++) {
		if(*s=='U') {
			if(level != 0) {
				level--;
				lrs--;
			}
		} else {
			level++;
			*lrs = *s;
			lrs++;
		}
	}
	*lrs = '\0';
	return level;
}

static N
calc_dynamic(N *nus, UEntry *us, char *s, N i)
{
	N lastn, n;
	char lastc;

	lastc = s[i];
	lastn = 1;
	us->r = us->l = 0;
	*nus = 0;
	if(lastc == 'U') {
		n = 1;
		us++;
		(*nus)++;
	} else if(lastc == 'L') {
		n = 2;
		us->l = 1;
	} else {
		n = 2;
		us->r = 1;
	}

	for(i--; i>=0; i--) {
		if(s[i] == 'U') {
			us->l = us[-1].l;
			us->r = us[-1].r;
			us++;
			(*nus)++;
			continue;
		}
		if(s[i] != lastc) {
			lastn = ((n+MOD_VAL) - lastn + 1) % MOD_VAL;
		}
		if(s[i] == 'R')
			us->r = n;
		else
			us->l = n;
		n = (n + lastn) % MOD_VAL;
		lastc = s[i];
	}
	return n;
}

static N
calc_result(UEntry *us, N nus, N n, N level, char *lrs)
{
	for(nus--, level--; nus >= 0 && level >= 0; nus--, level--) {
		if(lrs[level] == 'R')
			n = (n + 1 + us[nus].l) % MOD_VAL;
		else
			n = (us[nus].r + 1 + n) % MOD_VAL;
	}
	return n;
}

int
main()
{
	UEntry us[MAX_LEN];
	char s[MAX_LEN], t[MAX_LEN], lrs[MAX_LEN];
	N i, nus, n, level, res;
	int total;

	scanf("%d", &total);
	for(i=0; i<total; i++) {
		scanf("%s", s);
		scanf("%s", t);
		level = process_insts(lrs, s);
		n = calc_dynamic(&nus, us, t, ((N)strlen(t)) - 1);
		res = calc_result(us, nus, n, level, lrs);
		printf("Case %ld: %ld\n", i+1, res);
	}
	return 0;
}
