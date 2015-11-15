int N = 3;
int a[] = {1,2,3};
do {
    for (int i = 0; i < N; ++i) cout << a[i] << " ";
    cout << "\n";
}
while (next_permutation(a, a + N));

