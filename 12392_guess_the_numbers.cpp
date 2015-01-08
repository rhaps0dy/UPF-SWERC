#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

#define MAX_LEN 200

using namespace std;

int vars[5];

typedef struct PTree PTree;
struct PTree {
	int i;
	PTree *l, *r;
};

static int
eval_tree(PTree *pt)
{
	if(!pt->l)
		return vars[pt->i];
	switch(pt->i) {
		case ((int)'*'):
			return eval_tree(pt->l)*eval_tree(pt->r);
		case ((int)'-'):
			return eval_tree(pt->l)-eval_tree(pt->r);
		case ((int)'+'):
			return eval_tree(pt->l)+eval_tree(pt->r);
	}
	return -4000000;
}

static PTree *
ptree_new(char *beg, char *end)
{
	PTree *pt;
	int nparens;
	char *i;

	pt = (PTree *) malloc(sizeof(PTree));
	if(beg == end) {
		pt->i = (*beg)-'a'; 
		pt->l = pt->r = NULL;
	} else if(beg+4 == end) {
		pt->i = (int)beg[2];
		pt->l = ptree_new(beg+1, beg+1);
		pt->r = ptree_new(beg+3, beg+3);
	} else {
		i = beg+1;
		if(*i == '(') {
			i++;
			for(nparens=1; nparens!=0; i++) {
				if(*i=='(') nparens++;
				else if(*i==')') nparens--;
			}
			pt->l = ptree_new(beg+1, i-1);
		} else {
			pt->l = ptree_new(i, i);
			i++;
		}
		pt->i = (int)*i;
		beg = i;
		i++;
		if(*i == '(') {
			i++;
			for(nparens=1; nparens!=0; i++) {
				if(*i=='(') nparens++;
				else if(*i==')') nparens--;
			}
			pt->r = ptree_new(beg+1, i-1);
		} else {
			pt->r = ptree_new(i, i);
		}
	}

	return pt;
}

/*static void
ptree_print(PTree *pt)
{
	if(!pt->l) {
		printf("%d ", pt->i);
		return;
	}
	printf("%c ", pt->i);
	ptree_print(pt->l);
	ptree_print(pt->r);
	return;
}*/

static void
ptree_free(PTree *pt)
{
	if(!pt->l)
		free(pt);
	else {
		ptree_free(pt->l);
		ptree_free(pt->r);
		free(pt);
	}
}

static void
normalize(char *s)
{
	char c;

	c = 'a';
	for(; *s; s++)
		if(*s>='a' && *s <='z') {
			*s = c;
			c++;
		}
}

static int
compare_ints(const void *a, const void *b)
{
	int aa, bb;
	aa = *(int *)a;
	bb = *(int *)b;
	if(aa > bb) return 1;
	if(aa == bb) return 0;
	if(aa < bb) return -1;
}

int
main()
{
	PTree *pt;
	char equation[MAX_LEN];
	int i, n, v;

	for(;;) {
		scanf("%d", &n);
		if(n==0) return 0;

		for(i=0; i<n; i++)
			scanf("%d", &vars[i]);
		scanf("%d", &v);
		fgets(equation, MAX_LEN, stdin);
		fgets(equation, MAX_LEN, stdin);

		normalize(equation);
		pt = ptree_new(equation, equation+strlen(equation)-2);

/*		ptree_print(pt);
		putchar('\n');
		printf("%d - %d %d %d %d %d - %d\n", n, vars[0], vars[1], vars[2], vars[3], vars[4], v);*/

		qsort(vars, n, sizeof(int), compare_ints);
		i = 1;
		do {
			if(eval_tree(pt) == v) {
				puts("YES");
				goto after;
			}
//			printf("permutation n. %d: %d %d %d %d %d\n", i, vars[0], vars[1], vars[2], vars[3], vars[4]);
			i++;
		} while(next_permutation(vars, vars+n));
		puts("NO");
after:
		ptree_free(pt);
	}
	return 0;
}
