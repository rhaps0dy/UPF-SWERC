#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

pair<char, int> abc[26];

bool comp(const pair<char, int>& p1, const pair<char, int>&p2)
{
	if (p1.second > p2.second)
	{
		return true;
	}
	else if (p1.second == p2.second)
	{
		return p1.first < p2.first;
	}
	
	return false;
}

int main()
{
	int N = 0;
	cin >> N;
	
	for (int i = 0; i < 26; ++i)
	{
		abc[i].first = i + 'A';
		abc[i].second = 0;
	}
	
	string s = "";
	getline(cin, s);
	
	for (int i = 0; i < N; ++i)
	{
		getline(cin, s);
		
		for (int j = 0; j < s.length(); ++j)
		{
			char c = s[j];
			
			if (c >= 'a' && c <= 'z')
			{
				c -= ('a' - 'A');
			}
			
			if (c >= 'A' && c <= 'Z')
			{
				++abc[c - 'A'].second;
			}
		}
	}
	
	sort(abc, abc + 26, comp);
		
	for (int i = 0; i < 26 && abc[i].second != 0; ++i)
	{
		cout << abc[i].first << " " << abc[i].second << "\n";
	}

	return 0;
}

