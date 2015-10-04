#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int p[1001];
int v[1001];
int A[1001][1001];

#define MAX(A, B) ((A) > (B) ? (A) : (B))

int main()
{
    int C, N;


    while(cin >> C >> N) {
        for(int i=0; i<N; i++) {
            int w, h;
            cin >> w >> h >> v[i];
            p[i] = w * h * 4 + w * w;
        }

        for (int j = 0; j <= C; j++)
            A[0][j] = 0;
        for (int i = 1; i <= N; i++) {
            A[i][0] = 0;
            for (int j = 1; j <= C; j++) {
                A[i][j] = A[i-1][j];
                if (p[i-1] <= j) {
                    int r = A[i-1][j-p[i-1]] + v[i-1];
                    A[i][j] = MAX(A[i][j], r);
                }
            }
        }
        cout << A[N][C] << endl;
    }
    return 0;
}

