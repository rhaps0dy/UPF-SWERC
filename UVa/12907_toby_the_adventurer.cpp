#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

#define MAX_CITIES 10000
#define MAX_ROADS MAX_CITIES
#define MAX_COST 10001
#define X first
#define Y second
#define PB push_back
#define MP make_pair

vector<pair<int, int> > edge_entered; // edges used to enter each city. Store <cost, city_origin>
vector<vector<pair<int, int> > > adjacency; // adjacency list: <cost, city_destination>
int cost;
int n_accessible_cities;

static void
dfs_explore(int cur_city) {
    for(int i=0; i<(int)adjacency[cur_city].size(); i++) {
        int edge_cost = adjacency[cur_city][i].X;
        int other_city = adjacency[cur_city][i].Y;
        if(edge_entered[other_city].Y == -1) {
            n_accessible_cities++;
            cost += edge_cost;
            edge_entered[other_city].X = edge_cost;
            edge_entered[other_city].Y = cur_city;
            dfs_explore(other_city);
        } else if(edge_cost < edge_entered[other_city].X) {
            cost = cost - edge_entered[other_city].X + edge_cost;
            edge_entered[other_city].X = edge_cost;
            edge_entered[other_city].Y = cur_city;
        }
    }
}

int
main()
{
    int T;
    cin >> T;

    adjacency.reserve(MAX_CITIES);
    edge_entered.reserve(MAX_ROADS);
    const vector<pair<int, int> > empty_vector;

    while(T--) {
        int Ncities, Nroads, N0;
        cin >> Ncities >> Nroads >> N0;

        if(Nroads < Ncities - 1 || Ncities <= 1) {
            int discard;
            for(int i=0; i<Nroads; i++)
                cin >> discard >> discard >> discard;
            if(Ncities <= 1) {
                puts("0");
            } else {
                puts("impossible");
            }
            continue;
        }

        // initialize globals
        adjacency.assign(Ncities, empty_vector);
        edge_entered.assign(Ncities, MP(MAX_COST, -1));
        for(int i=0; i<Nroads; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adjacency[u].PB(MP(w, v));
        }
        cost = 0;
        n_accessible_cities = 1;
            

        dfs_explore(N0);
        if(n_accessible_cities < Ncities) {
            puts("impossible");
            continue;
        }
        if(Ncities <= 1) {
            puts("0");
            continue;
        }

        printf("%d\n", cost);
        for(int i=0; i<Ncities; i++) {
            if(i != N0) {
                printf("%d %d %d\n", edge_entered[i].Y, i, edge_entered[i].X);
            }
        }
    }
    return 0;
}
