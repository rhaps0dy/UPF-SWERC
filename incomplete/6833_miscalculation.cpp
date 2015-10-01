#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int N[20];
bool O[20];
int NN;

int computeInOrder()
{
	int num = N[0];
	
	for (int i = 1; i < NN; ++i)
	{
		if (O[i - 1])
		{
			num += N[i];
		}
		else
		{
			num *= N[i];
		}
	}
	
	return num;
}

int computePriorize()
{
	int num = 0;
	int currentMult = 0;
	
	bool multiplying = false;
	
	for (int i = 0; i < NN-1; ++i)
	{
		if (O[i]) // sum
		{
			if (multiplying)
			{
				num += currentMult;
				multiplying = false;
			}
		}		
		else
		{
			if (multiplying)
			{
				currentMult *= N[i + 1];
			}
			else
			{
				currentMult = N[i] * N[i + 1];
				multiplying = true;
			}
		}
	}
	
	if (multiplying)
	{
		num += currentMult;
	}
	
	if (O[0])
	{
		num += N[0];
	}	
	
	for (int i = 1; i < NN; ++i)
	{
		if (O[i-1] && O[i])
		{
			num += N[i];
		}
	}
	
	if (NN >= 2 && O[NN - 2])
	{
		num += N[NN -1];
	}
		
	return num;
}

int main()
{
	string l = "";
	
	while (getline(cin, l))
	{
		if (l != "")
		{
			int bobanswer = 0;
			cin >> bobanswer;
						
			int inorder = 0;
			int priorized = 0;
			
			if (l.length() == 1)
			{
				inorder = priorized = l[0] - '0';
			}
			else if (l.length() > 1)
			{
				int k = 0;
				
				for (int i = 0; i < l.length() - 2; i += 2, ++k)
				{
					N[k] = l[i] - '0';
					O[k] = l[i + 1] == '+';
				}
								
				N[k] = l[l.length() - 1] - '0';
				NN = k+1;
				/*
				for (int i = 0; i < NN; ++i)
				{
					cout << N[i] << " ";
					
					if (i != NN - 1)
					{
						cout << O[i] << " ";
					}
				}
				
				cout << endl;
				*/
				inorder = computeInOrder();
				priorized = computePriorize();
			}
						
			//cout << "answer " << bobanswer << endl;
			
			bool priorBob = priorized == bobanswer;
			bool orderBob = inorder == bobanswer;
			
			//cout << priorized << " " << inorder << endl;
			
			if (priorBob)
			{
				if (orderBob) cout << "U\n";
				else cout << "M\n";
			}
			else if (orderBob) cout << "L\n";
			else cout << "I\n";
		}
	}
	
	return 0;
}

