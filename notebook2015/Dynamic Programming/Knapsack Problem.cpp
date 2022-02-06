#include<iostream>
#include<utility>
using namespace std;

int N = 8; // numero de objetos N <= 1000
int v[] = {1,6,7,1,8,3,7,5}; // valor de objetos
int p[] = {5,3,7,1,8,2,7,3}; // peso de objetos
int A[1001][1001]; // matriz de resultados
int comes_from[1001][1001];

int main() {
    int C = 7; // capacidad C <= 1000

    for (int j = 0; j <= C; j++)
        A[0][j] = 0;
    for (int i = 1; i <= N; i++) {
        A[i][0] = 0;
        for (int j = 1; j <= C; j++) {
            A[i][j] = A[i-1][j];
            if (p[i-1] <= j) {
                int r = A[i-1][j-p[i-1]] + v[i-1];
				if(A[i][j] > r) {
				} else {
					comes_from[i][j] = i;
					A[i][j] = r;
				}
            }
        }
    }
	for(int i=0; i<=N; i++) {
		for(int j=0; j<=C; j++)
			cout << comes_from[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	cout << endl;


	int i=N, j=C;
	while(i>0 && j>0) {
		if(comes_from[i][j] == 0) {
			i -= 1;
		} else {
			cout << comes_from[i][j]-1 << ", ";
			j -= p[comes_from[i][j]-1];
			i -= 1;
		}
	}
    cout << endl << A[N][C] << endl; // output: 12
	return 0;
}
