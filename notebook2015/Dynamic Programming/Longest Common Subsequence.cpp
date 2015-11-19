table[_][0] = 0;
for(int i=1; i<n+1; i++) {
    table[i][0] = 0;
    for(int j=1; j<n+1; j++) {
        if(x[i-1] == y[j-1])
            table[i][j] = table[i-1][j-1] + 1;
        else
            table[i][j] = max(table[i-1][j], table[i][j-1]);
    }
}
