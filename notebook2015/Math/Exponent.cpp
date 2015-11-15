template <typename T,typename U> T expo(T &t, U n) {
    if (n == U(0)) return T(1);
    else {
        T u = expo(t, n/2);
        if (n%2 > 0) return u*u*t; 
        else return u*u;
    }
}
