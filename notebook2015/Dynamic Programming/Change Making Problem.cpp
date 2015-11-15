int N = 8; // numero de monedas
int m[] = {1,2,5,10,20,50,100,200}; // monedas
int A[100001]; // vector de resultados

int main() {
    int C; // monto C <= 100000
    cin >> C;  
    A[0] = 0;
    for (int i = 1; i <= C; i++) {
        A[i] = 1000000;
        for (int j = 0; j < N && m[j] <= i; j++)
            A[i] = MIN(A[i], A[i-m[j]] + 1);
    }
    cout << A[C] << endl;
}
