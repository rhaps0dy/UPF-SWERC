const int MAX_LEN = 262144 * 2;
cpx A[MAX_LEN], B[MAX_LEN], C[MAX_LEN];
int A_len, B_len, C_len;

/* set the appropriate coefficients in the inputs A and B's real-valued part,
 * and their length in A_len and B_len. */

for(C_len = 1; !(C_len > A_len + B_len - 1); C_len *= 2);
assert(C_len < MAX_LEN); 
memset(A + A_len, 0, (C_len - A_len) * sizeof(cpx));
memset(B + B_len, 0, (C_len - B_len) * sizeof(cpx));
FFT(A, C, 1, C_len, 1);
FFT(B, A, 1, C_len, 1);
for(int i=0; i<C_len; i++)
    A[i] = A[i] * C[i];
FFT(C, A, 1, C_len, -1);
for(int i=0; i<C_len; i++)
    C[i].a /= C_len;
// now C[i].a (the real-valued parts) contain the result
