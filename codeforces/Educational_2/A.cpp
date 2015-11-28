#include<bits/stdc++.h>

using namespace std;

void print(const vector<int> &a, const string &s) {
	if(a.size() == 0) {
		putchar('-');
	} else {
		putchar('"');
		for(int j=a[0]; j < s.size() && s[j] != ';' && s[j] != ','; j++)
			putchar(s[j]);
		for(int i=1; i<a.size(); i++) {
			putchar(',');
			for(int j=a[i]; j < s.size() && s[j] != ';' && s[j] != ','; j++)
				putchar(s[j]);
		}
		putchar('"');
	}
	putchar('\n');
}

int main() {
	string s;
	cin >> s;
	vector<int> a, b;
	int s_size = (int) s.size();
	int i=0;
	while(i < (int)s_size) {
		if(s[i] == ',' || s[i] == ';') {
			b.push_back(i);
			i++;
		} else if(s[i] == '0') {
			if(i == s_size-1 || s[i+1] == ',' || s[i+1] == ';') {
				a.push_back(i);
				i += 2;
			} else {
				b.push_back(i);
				for(; i < s_size && s[i] != ',' && s[i] != ';'; i++);
				i++;
			}
		} else {
			int j = i;
			for(; i < s_size && s[i] >= '0' && s[i] <= '9'; i++);
			if(i >= s_size || s[i] == ',' || s[i] == ';')
				a.push_back(j);
			else {
				b.push_back(j);
				for(; i < s_size && s[i] != ';' && s[i] != ','; i++);
			}
			i++;
		}
	}
	if(s_size > 0 && (s[s_size-1] == ',' || s[s_size-1] == ';'))
		b.push_back(s_size-1);
	print(a, s);
	print(b, s);
	return 0;
}
