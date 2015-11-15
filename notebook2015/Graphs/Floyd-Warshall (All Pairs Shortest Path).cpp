// Complexity: n^3
// A: matriz n*n de adyacencia con costes
// ausencia de arista representada por un numero grande
for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = MIN(A[i][j], A[i][k] + A[k][j]);
