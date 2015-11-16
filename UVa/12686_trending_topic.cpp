/**
 * Trending Topic
 * Problem 12686 UVA
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=602&page=show_problem&problem=4424
 */

#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <string>
#include <assert.h>
#include <algorithm>

using namespace std;

struct cmpStruct
{
	bool operator() (const pair<int, string>& lhs, const pair<int, string>& rhs) const
	{
		if (lhs.first == rhs.first)
		{
			return lhs.second < rhs.second;
		}

		return lhs.first > rhs.first;
	}
};

// For mantaining last days
map<string, int> lastDays[7];
int filledDays = 0;
int currIndex = 0;

// For tops
map<string, int> topOrderMap;
set< pair<int, string>, cmpStruct> topOrderSet;
int topNumber = 0;

void putWordInCurrentDay(string& word)
{
	map<string, int>::iterator it = lastDays[currIndex].find(word);

	if (it == lastDays[currIndex].end())
	{
		lastDays[currIndex][word] = 1;
	}
	else
	{
		++lastDays[currIndex][word];
	}
}

void putWordInTotals(string& word)
{
	map<string, int>::iterator topOrderMapIt = topOrderMap.find(word);

	if (topOrderMapIt == topOrderMap.end())
	{
		topOrderMap[word] = 1;
		topOrderSet.insert(make_pair(1, word));
	}
	else
	{
		int numOccurrences = topOrderMapIt->second;
		++(topOrderMapIt->second);
		topOrderSet.erase(make_pair(numOccurrences, word));
		topOrderSet.insert(make_pair(numOccurrences + 1, word));
	}
}

void eraseCurrentDayDataFromTotals()
{
	map<string, int>& currentDay = lastDays[currIndex];

	for (map<string, int>::iterator it = currentDay.begin(); it != currentDay.end(); ++it)
	{
		// Get iterator of the word in the map
		map<string, int>::iterator topOrderMapIt = topOrderMap.find(it->first);
		assert(topOrderMapIt != topOrderMap.end());

		// Get number of global occurrences in the map
		int globalOccurrences = topOrderMapIt->second;

		// Create the pair that appears in the set and look for it
		pair<int, string> globalWordItem(globalOccurrences, it->first);
		set< pair<int, string> >::iterator topOrderSetIt = topOrderSet.find(globalWordItem);
		assert(topOrderSetIt != topOrderSet.end());

		topOrderSet.erase(topOrderSetIt);

		topOrderMapIt->second = topOrderMapIt->second - it->second;

		if (topOrderMapIt->second == 0)
		{
			topOrderMap.erase(topOrderMapIt);
		}
		else
		{
			topOrderSet.insert(make_pair(topOrderMapIt->second, it->first));
		}
	}

	currentDay.clear();
}

void printTop()
{
	cout << "<top " << topNumber << ">" << endl;

	set< pair<int, string> >::iterator it = topOrderSet.begin();

	int lastRank = 0;

	for (int n = 0; (n < topNumber) && (it != topOrderSet.end()); ++it, ++n)
	{
		cout << it->second << " " << it->first << endl;

		lastRank = it->first;
	}

	while ((it != topOrderSet.end()) && (it->first == lastRank))
	{
		cout << it->second << " " << it->first << endl;
		++it;
	}

	cout << "</top>" << endl;
}

int main()
{
	string strToken = "";

	while (cin >> strToken)
	{
		if (strToken == "<text>")
		{
			if (filledDays >= 7)
			{
				eraseCurrentDayDataFromTotals();
			}

			while (cin >> strToken)
			{
				if (strToken == "</text>")
				{
					currIndex = (currIndex + 1) % 7;
					filledDays = min(filledDays + 1, 7);
					break;
				}

				if (strToken.length() < 4) continue;

				putWordInCurrentDay(strToken);
				putWordInTotals(strToken);
			}
		}
		else if (strToken == "<top")
		{
			cin >> topNumber;
			printTop();
		}
	}

	return 0;
}

















