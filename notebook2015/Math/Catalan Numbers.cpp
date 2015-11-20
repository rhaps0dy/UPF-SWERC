unsigned long long v[34]; // 1, 1, 2, 5, 14, 42, 132, 429, 1430, ...
// Cn = number of strings of n*2 consistent parentheses.
// ((())) ()(()) ()()() (())() (()())
// Cn = number of non-isomorphic ordered trees with n vertices.
// Cn = number of full binary trees with n + 1 leaves, and n internal nodes
// Cn = number of ways to tile a stairstep shape of height n with n rectangles
/* Cn = number of monotonic lattice paths along the edges of a grid with n × n
   square cells, which do not pass above the diagonal */
void catalan(){
    v[0] = 1;
    for (int i = 1; i < 34; ++i){
        unsigned long long sum = 0;
        for (int j = 0; j < i; ++j){
            sum += v[j] * v[i-j-1];
        }
        v[i] = sum;
    }
}
