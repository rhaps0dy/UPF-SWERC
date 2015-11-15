int N = 8; // numero de objetos N <= 1000
int v[] = {1,6,7,1,8,3,7,5}; // valor de objetos
int p[] = {5,3,7,1,8,2,7,3}; // peso de objetos
int A[1001][1001]; // matriz de resultados

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
                A[i][j] = MAX(A[i][j], r);
            }
        }
    }
    cout << A[N][C] << endl; // output: 12
}
