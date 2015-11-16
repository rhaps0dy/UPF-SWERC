#include <iostream>
#include <stack>

using namespace std;

typedef struct Plates
{
	long n; // quantity of plates
	long a; // age of the plates
} Plates;

stack<Plates>* P1;
stack<Plates>* P2;

long M; // number of plates about the order
string O; // order to execute

long N; // number of instructions
long A = 0; // age identifier

void doAction()
{
	if (O == "DROP")
	{
		Plates p;
		p.n = M;
		p.a = A++;

		cout << "DROP 2 " << p.n << endl;
		P2->push(p);
	}
	else if (O == "TAKE")
	{
		if (!P1->empty() && !P2->empty())
		{
			long toTake = M;

			while ((toTake != 0) && !P1->empty())
			{
				Plates& top = P1->top();

				if (toTake < top.n)
				{
					top.n -= toTake;
					toTake = 0;
				}
				else
				{
					toTake -= top.n;
					P1->pop();
				}
			}

			cout << "TAKE 1 " << M - toTake << endl;

			if (toTake != 0)
			{
				long moved = 0;

				while (!P2->empty())
				{
					moved += P2->top().n;

					P1->push(P2->top());
					P2->pop();
				}

				cout << "MOVE 2->1 " << moved << endl;

				long beingtaken = toTake;

				while (toTake != 0)
				{
					Plates& top = P1->top();

					if (toTake < top.n)
					{
						top.n -= toTake;
						toTake = 0;
					}
					else
					{
						toTake -= top.n;
						P1->pop();
					}	
				}

				cout << "TAKE 1 " << beingtaken << endl; 
			}
		}
		else if (!P1->empty())
		{
			long toTake = M;

			while (toTake != 0)
			{
				Plates& top = P1->top();

				if (toTake < top.n)
				{
					top.n -= toTake;
					toTake = 0;
				}
				else
				{
					toTake -= top.n;
					P1->pop();
				}
			}

			cout << "TAKE 1 " << M << endl;
		}
		else if (!P2->empty())
		{
			long moved = 0;

			while (!P2->empty())
			{
				moved += P2->top().n;

				P1->push(P2->top());
				P2->pop();
			}

			cout << "MOVE 2->1 " << moved << endl;

			long toTake = M;

			while (toTake != 0)
			{
				Plates& top = P1->top();

				if (toTake < top.n)
				{
					top.n -= toTake;
					toTake = 0;
				}
				else
				{
					toTake -= top.n;
					P1->pop();
				}	
			}

			cout << "TAKE 1 " << M << endl; 
		}
		else
		{
			cout << "SHOULD NOT HAPPEN" << endl;
		}
	}
}

int main()
{
	while (cin >> N)
	{
		if (!N) break;

		P1 = new stack<Plates>;
		P2 = new stack<Plates>;

		M = 0;
		O = "";

		for (long i = 0; i < N; ++i)
		{
			cin >> O >> M;
			doAction();
		}

		cout << endl;

		delete P1;
		delete P2;
	}

	return 0;
}