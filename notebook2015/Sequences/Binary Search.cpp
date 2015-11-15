// binary_search function can be found at algorithm library
// devuelve el i mas pequeno tal que t <= v[i]
// si no existe tal i, devuelve v.SZ
template<typename T> int bb(T t, vector<T> &v) {
    int a = 0, b = v.SZ;
    while (a < b) {
        int m = (a + b)/2;
        if (v[m] < t) a = m+1;  else b = m;
    }
    return a;
}
