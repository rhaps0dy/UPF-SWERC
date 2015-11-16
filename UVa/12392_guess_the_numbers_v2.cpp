#include <iostream>
#include <algorithm>

using namespace std;

int U = 0; // # unknowns
int V[51]; // unknown values
int M = 0; // desired result
int N = 0; // value on V to be assigned
int P = 0; // current position in reading expression
string E = "";

typedef struct expr
{
	expr* lhs;
	expr* rhs;
	char op;
	int* val;
} expr;

expr* parseExpression()
{
	expr* e = new expr;

	if (E[P] == '(')
	{
		++P;
		e->lhs = parseExpression();
		
		e->op = E[P++];
		
		e->rhs = parseExpression();

		++P;
	}
	else
	{
		e->val = V + (N++);
		e->lhs = NULL;
		e->rhs = NULL;
		++P;
	}

	return e;
}

int evaluateExpression(expr* e)
{
	if (e->lhs && e->rhs)
	{
		int val1 = evaluateExpression(e->lhs);
		int val2 = evaluateExpression(e->rhs);

		switch(e->op)
		{
			case '+':
				return val1 + val2;
			case '-':
				return val1 - val2;
			case '*':
				return val1 * val2;
		}
	}
	else if (!e->lhs && !e->rhs)
	{
		return *(e->val);
	}

	return 0;
}

int main()
{
	while (cin >> U)
	{
		if (U == 0) break;

		for (int i = 0; i < U; ++i)
		{
			cin >> V[i];
		}

		sort(V, V+U); // must sort to get all permutations

		cin >> M;

		cin >> E;

		N = P = 0;

		expr* e = parseExpression();

		bool found = false;

		do
		{
			int r = evaluateExpression(e);

			if (r == M)
			{
				found = true;
				break;
			}
		}
		while (next_permutation(V, V+U));

		if (found)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}

	return 0;
}