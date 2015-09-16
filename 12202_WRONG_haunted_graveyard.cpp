#include <algorithm>
#include <set>
#include <vector>
#include <cstdio>

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


using namespace std;

typedef pair<pair<int,int>,int> P; // par de nodos + coste
int N;                             // numero de nodos
vector<P> v;                       // representacion aristas

int bellmanford(int a, int b) {
  vector<int> d(N, 1000000000);
  int dist;

  d[a] = 0;
  for (int i = 1; i < N; i++)
    for (int j = 0; j < (int)v.SZ; j++)
      if (d[v[j].X.X] < 1000000000 && 
      (dist = d[v[j].X.X] + v[j].Y) < d[v[j].X.Y])
        d[v[j].X.Y] = dist;
  for(int i=0; i<N; i++)
	  if (d[v[i].X.X] < 1000000000 &&
		d[v[i].X.X] + v[i].Y < d[v[i].X.Y])
		  return -1000000000; // existe ciclo negativo
  return d[b];
}

#define INDOF(j, i) ((j)*w + (i))

int
main()
{
	int w, h, ngraves, nholes, i, j, x, y, cost, y2, x2, setnever, thisn, othern;
	set<int> gravestones;
	
	for(;;) {
		scanf("%d %d", &w, &h);
		N = w*h;
		if(w==0) break;
		gravestones.clear();
		v.clear();

		scanf("%d", &ngraves);
		for(i=0; i<ngraves; i++) {
			scanf("%d %d", &x, &y);
			gravestones.insert(INDOF(x, y));
		}

/*		for(set<int>::iterator iter = gravestones.begin(); iter != gravestones.end(); iter++)
			printf("%d %d\n", *iter / w, *iter % w);
		putchar('\n'); */
		
		for(j=0; j<h; j++)
			for(i=0; i<w; i++) {
				if(j==h-1 && i==w-1) break;

				thisn = INDOF(j, i);
				if(gravestones.find(thisn) != gravestones.end()) continue;

				if(j>0 && gravestones.find(othern=INDOF(j-1, i)) == gravestones.end())
					v.PB(MP(MP(othern, thisn), 1));

				if(j<h-1 && gravestones.find(othern=INDOF(j+1, i)) == gravestones.end())
					v.PB(MP(MP(othern, thisn), 1));

				if(i>0 && gravestones.find(othern=INDOF(j, i-1)) == gravestones.end())
					v.PB(MP(MP(othern, thisn), 1));

				if(i<w-1 && gravestones.find(othern=INDOF(j, i+1)) == gravestones.end())
					v.PB(MP(MP(othern, thisn), 1));
			}
		
		scanf("%d", &nholes);
		setnever = 0;
		for(i=0; i<nholes; i++) {
			scanf("%d %d", &x, &y);
			scanf("%d %d", &x2, &y2);
			scanf("%d", &cost);
			if(x==x2 && y==y2) {
				if(cost>=0) continue;
				else setnever=1;
			}
			v.PB(MP(MP(INDOF(y, x), INDOF(y2, x2)), cost));
		}
		if(setnever) {
			puts("Never");
			continue;
		}
		
		/* print graph */
		for(i=0; i < (int)v.SZ; i++)
			printf("%d %d, %d %d, %d\n", (v[i].X.X%w), (v[i].X.X/w), (v[i].X.Y%w), (v[i].X.Y/w), v[i].Y);
		putchar('\n');
		cost=bellmanford(INDOF(0, 0), INDOF(h-1, w-1));
		if(cost <= -1000000000)
			puts("Never");
		else if(cost >= 1000000000)
			puts("Impossible");
		else
			printf("%d\n", cost);
	}
	return 0;
}
