#include <utility>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <stdio.h>

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


const int INF = 2000000000;
typedef pair<int,int> PII;

int dijkstra(int N, vector<vector<PII> > &edges, int s, int t) {
 // use priority queue in which top element has the "smallest" priority
  priority_queue<PII, vector<PII>, greater<PII> > Q;
  vector<int> dist(N, INF), dad(N, -1);
  Q.push (make_pair (0, s));
  dist[s] = 0;
  while (!Q.empty()){
    PII p = Q.top();
    if (p.second == t) break;
    Q.pop();
    
    int here = p.second;
    for (vector<PII>::iterator it=edges[here].begin(); it!=edges[here].end(); it++){
      if (dist[here] + it->first < dist[it->second]){
        dist[it->second] = dist[here] + it->first;
        dad[it->second] = here;
        Q.push (make_pair (dist[it->second], it->second));
      }
    }
  }
  return dist[t];
}

int
main()
{
    int E, N;
    while(cin >> N) {
	map<string, int> cities;
	vector<vector<PII> > edges(N*2);
	for(int i=0; i<N; i++) {
	    string city;
	    cin >> city;
	    cities.insert(MP(city, i*2));
	    // same city odd day to even day
	    edges[i*2].PB(MP(1, i*2+1));
	    edges[i*2+1].PB(MP(1, i*2));
	}
	cin >> E;
	for(int i=0; i<E; i++) {
	    string na, nb;
	    cin >> na >> nb;
	    int ia = cities[na];
	    int ib = cities[nb];
	    bool even = (i % 2 == 0);

	    if(even) {
		// road is open on even days
		edges[ia].PB(MP(1, ib+1));
		edges[ib].PB(MP(1, ia+1));
	    } else {
		// road open on odd days
		edges[ia+1].PB(MP(1, ib));
		edges[ib+1].PB(MP(1, ia));
	    }
	}

	int r = cities["Rome"];
	int v = cities["Venice"];
	cout << MIN(dijkstra(N*2, edges, r, v), dijkstra(N*2, edges, r, v+1)) << endl;
    }
    return 0;
}
