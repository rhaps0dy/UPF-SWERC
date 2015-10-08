#include<iostream>
#include<vector>
#include<utility>


using namespace std;

#define X first
#define Y second
#define LI long long
#define MP make_pair
#define PB push_back
#define SZ size()
#define SQ(a) ((a)*(a))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define FOR(i,x,y) for(int i=(int)x; i<(int)y; i++)
#define RFOR(i,x,y) for(int i=(int)x; i>(int)y; i--)
#define SORT(a) sort(a.begin(), a.end())
#define RSORT(a) sort(a.rbegin(), a.rend())
#define IN(a,pos,c) insert(a.begin()+pos,1,c)
#define DEL(a,pos,cant) erase(a.begin()+pos,cant)

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

int main(){
    int n ;
    while(cin>>n)
    {
        vector<P> dentro , fuera , convexin;
        int ni;
        P p;
        cin>>ni;
        for(int i = 0 ; i < ni ; ++i)
        {
            cin>>p.X>>p.Y;
            dentro.push_back(p);
        }
        cin>>ni;
        for(int i = 0 ; i < ni ; ++i)
        {
            cin>>p.X>>p.Y;
            fuera.push_back(p);

        }

        convexin = convexhull(dentro);

        for(int i = 0 ; i < convexin.size())
    }

}
