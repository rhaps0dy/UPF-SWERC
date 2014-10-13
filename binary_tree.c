#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD_VAL 21092013
#define MAX_LEN 100001

typedef long N;

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

/* calculates the number of nodes per suffix and stores it in nnodes.
stores the indices of all Us in us, the end is marked with a MAX_LEN value
s is the character sequence, i is the index of last char */
static void
calc_dynamic(N *nnodes, N *us, char *s, N i)
{
	N lastn;
	char lastc;

	lastc = s[i];
	lastn = 1;
	if(lastc == 'U') {
		nnodes[i] = 1;
		*us = i;
		us++;
	} else
		nnodes[i] = 2;

	for(i--; i>=0; i--) {
		if(s[i] == 'U') {
			nnodes[i] = nnodes[i+1];
			*us = i;
			us++;
			continue;
		}
		if(s[i] != lastc)
			lastn = (nnodes[i+1] - lastn + 1) % MOD_VAL;
		nnodes[i] = (nnodes[i+1] + lastn) % MOD_VAL;
		lastc = s[i];
	}

	*us = MAX_LEN;
}

/* calculates the number of possible nodes you can reach from a given tree
level, sequence, and precalculated values from calc_dynamic */
static N
calc_n(N level, N *nnodes, N i, N *us)
{
	N total;

	total = 0;
}

int
main()
{
	char s[MAX_LEN], lrs[MAX_LEN];
	N nnodes[MAX_LEN], us[MAX_LEN], i, level;

	scanf("%s", s);
	level = process_insts(lrs, s);
	puts(lrs);
	printf("level %ld\n", level);

	/*calc_dynamic(nnodes, us, s, sizeof(s)-2);

	puts(s);
	for(i=0; i<sizeof(s)-1; i++)
		printf("%d ", nnodes[i]);
	putchar('\n');

	for(i=0; us[i]!=MAX_LEN; i++)
		printf("%d ", us[i]);
	putchar('\n');*/
	return 0;
}
