typedef int T;     // posiblemente cambiar a double
typedef pair<T,T> P;
T xp(P p, P q, P r) {
    return (q.X-p.X)*(r.Y-p.Y) - (r.X-p.X)*(q.Y-p.Y);
}
struct Vect {
    P p, q;  T dist;
    Vect(P &a, P &b) {
        p = a;  q = b;
        dist = SQ(a.X - b.X) + SQ(a.Y - b.Y);
    }
    bool operator<(const Vect &v) const {
        T t = xp(p, q, v.p);
        return t < 0 || t == 0 && dist < v.dist;
    }
};

vector<P> convexhull(vector<P> v) { // v.SZ >= 2
    sort(v.begin(), v.end());
    vector<Vect> u;
    for (int i = 1; i < (int)v.SZ; i++)
        u.PB(Vect(v[i], v[0]));
    sort(u.begin(), u.end());
    vector<P> w(v.SZ, v[0]);
    int j = 1;  w[1] = u[0].p;
    for (int i = 1; i < (int)u.SZ; i++) {
        T t = xp(w[j-1], w[j], u[i].p);
        for (j--; t < 0 && j > 0; j--)
            t = xp(w[j-1], w[j], u[i].p);
        j += t > 0 ? 2 : 1;
        w[j] = u[i].p;
    }
    w.resize(j+1);
    return w;
}

int main() {
    vector<P> v;
    v.PB(MP(0, 1));
    v.PB(MP(1, 2));
    v.PB(MP(3, 2));
    v.PB(MP(2, 1));
    v.PB(MP(3, 1));
    v.PB(MP(6, 3));
    v.PB(MP(7, 0));
    vector<P> w = convexhull(v);
} // resultado: (0,1) (7,0) (6,3) (1,2)
