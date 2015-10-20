#include<iostream>

using namespace std;

int main() {
	int X, Y; int a; int N;
	int i;
	while(cin >> X >> Y) {
		cin >> N;
		for(i=0; i<N; i++) {
			cin >> a;
			if(a <= 0) {
				cout << "NO" << endl;
				continue;
			}
			if(a == 1) {
				cout << "YES" << endl;
				continue;
			}
//			cout << X << ' ' << Y << ' ' << N << ' ' << a << endl;
			bool x = X%a == 0;
			bool x1 = (X-1)%a == 0;
			bool x2 = (X-2)%a == 0;
			bool y = Y%a == 0;
			bool y1 = (Y-1)%a == 0;
			bool y2 = (Y-2)%a == 0;
			if((x2 && y) || (y2 && x) || (y1 && x1) || (x1 && y2 && y) || (y1 && x2 && x))
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
	}
	return 0;
}
