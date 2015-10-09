/**
 * Author: Daniel F.B. (Ertsiger)
 * 09/10/2015
 * Time: 0.000
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> A[101]; // adjacency list (directed graph without cycles)
int inbound[101]; // number of nodes that point to each node
vector<int> fo; // final order

void toposort( int M ) {
	stack<int> order;
	int current;

	// Search for roots
	for(int m = 1; m <= M; m++){
		if( inbound[m] == 0 )
			order.push( m ) ;
	}

	// Start topsort from roots
	while( !order.empty() ){
		// Pop from stack 
		current = order.top();
		order.pop();
		// Save order in fo
		fo.push_back( current );
		// Add childs only if inbound is 0
		for (int i = 0; i < A[current].size(); ++i)
		{
			inbound[A[current][i]]--;
			if (inbound[A[current][i]] == 0)
				order.push(A[current][i]);
		}
	}
}

int main()
{
	int M; // number of nodes
	int N; // number of precedence relations

	while (cin >> M >> N)
	{
		if (!M && !N) break;
		
		fo.clear();
		
		for (int i = 0; i <= M; ++i)
		{
			A[i].clear();
			inbound[i] = 0;
		}
		
		int m1, m2;
		
		for (int i = 0; i < N; ++i)
		{
			cin >> m1 >> m2;
			A[m1].push_back(m2);
			++inbound[m2];
		}
		
		toposort(M);
		
		for (int i = 0; i < fo.size(); ++i)
		{
			if (i > 0)
			{
				cout << " ";
			}
			
			cout << fo[i];
		}
		
		cout << endl;
	}
	
	return 0;
}

