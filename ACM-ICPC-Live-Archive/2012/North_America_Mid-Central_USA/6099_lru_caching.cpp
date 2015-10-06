/**
 * Author: Daniel Furelos Blanco (Ertsiger)
 * 21/09/2015
 * Time: 0.003
 */
#include <iostream>
#include <string>
#include <set>
#include <sstream>

using namespace std;

typedef struct Access{
	char c;
	int t; // last time accessed
	
	Access(char cc, int tt): c(cc), t(tt){}
} Access;

struct compare
{
	bool operator()(const Access& lhs, const Access& rhs)
	{
		if (lhs.t == rhs.t)
		{
			return lhs.c < rhs.c;
		}
		
		return lhs.t < rhs.t;
	}
};

int L[128]; // last access
set<Access, compare> cache;
int cacheSize = 0;


void remove(char c)
{
	Access a(c, L[c]);
	set<Access, compare>::iterator it = cache.find(a);
	
	if (it != cache.end())
	{
		cache.erase(it);
	}
}

void insert(char c, int t)
{
	L[c] = t;
	Access b(c, L[c]);
	
	if (cache.size() == cacheSize)
	{
		cache.erase(cache.begin());
	}
	
	cache.insert(b);
}

void print()
{
	for (set<Access, compare>::iterator it = cache.begin(); it != cache.end(); ++it)
	{
		cout << it->c;
	}
	
	cout << endl;
}

int main()
{	
	int simuln = 1;

	while (cin >> cacheSize)
	{
		if (cacheSize == 0) break;
		
		cout << "Simulation " << simuln++ << endl;
		
		for (int i = 0; i < 128; ++i) L[i] = -1;

		cache.clear();
		
		string line = "";
		getline(cin, line);
		
		for (int i = 0; i < line.length(); ++i)
		{
			char c = line[i];
			
			if (c == '!')
			{
				print();
			}
			else if (c != ' ')
			{
				if (L[c] != -1) // has accessed before
				{
					remove(c);
				}
				
				insert(c, i);
			}
		}
	}

	return 0;
}

