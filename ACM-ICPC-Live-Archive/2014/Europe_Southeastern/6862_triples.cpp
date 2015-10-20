#include<iostream>

using namespace std;

int squares[10001];

int main() {
	for(int i=0; i<=100; i++)
		squares[i*i] = i;
	int M, N;
	while(cin >> M >> N) {
		int total=0;
		for(int i=1; i<=M; i++) {
			for(int j=i; j<=M; j++) {
				int n = i*i + j*j;
				if(n <= 10000 && squares[n] >= j && squares[n] <= M)
					total++;
			}
		}
		total += (M+1) * (N - 1);
		cout << total << endl;
	}
	return 0;
}
