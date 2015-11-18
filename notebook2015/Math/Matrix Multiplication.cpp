#define SIZE 15    // tamano de matriz cuadrado
#define MOD 10007  // modulo de la multiplicacion
struct matriz {
    int v[SIZE][SIZE];
    matriz() { init(); } // matriz de 0's
    matriz(int x) {      // matriz con x's en la diagonal
        init();
        for (int i = 0; i < SIZE; i++) v[i][i] = x;
    }
    void init() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++) v[i][j] = 0;
    }
    // multiplicacion de matrices modulo MOD
    matriz operator*(matriz &m) {
        matriz n;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for (int k = 0; k < SIZE; k++)
                    n.v[i][j] = (n.v[i][j] + v[i][k]*m.v[k][j])%MOD;
        return n;
    }
};