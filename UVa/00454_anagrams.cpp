#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isAnagram(const string& w1, const string& w2)
{
	string w1p = w1;
	string w2p = w2;

	w1p.erase(remove(w1p.begin(), w1p.end(), ' '), w1p.end());
	w2p.erase(remove(w2p.begin(), w2p.end(), ' '), w2p.end());

	if (w1p.length() == w2p.length())
	{
		vector<bool> revChar;
		revChar.resize(w2p.length());

		for (int i = 0; i < (int)w1p.length(); ++i)
		{
			for (int j = 0; j < (int)w2p.length(); ++j)
			{
				if ((w1p[i] == w2p[j]) && !revChar[j])
				{
					revChar[j] = true;
					break;
				}
				else if (j == (w2p.length() - 1))
				{
					return false;
				}
			}
		}

		return true;
	}

	return false;
}

int main()
{
	int testCases = 0;
	cin >> testCases;

	string word = " ";
	getline(cin, word);
	getline(cin, word);

	for (int i = 0; i < testCases; ++i)
	{
		vector<string> words;

		while (getline(cin, word))
		{
			if (word == "")
				break;

			words.push_back(word);
			// cout << word << endl;
		}

		sort(words.begin(), words.end());

		for (int j = 0; j < (int)words.size() - 1; ++j)
		{
			for (int k = j + 1; k < (int)words.size(); ++k)
			{
				if (isAnagram(words[j], words[k]))
				{
					cout << words[j] << " = " << words[k] << endl;
				}
			}
		}

		if (i != (testCases - 1))
		{
			cout << endl;
		}
	}

	return 0;
}