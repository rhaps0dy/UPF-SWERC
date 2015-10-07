#include <stdio.h>
#include <vector>
#include <utility>
#include <limits.h>

using namespace std;

static constexpr int MAX_NODES = 17;
static constexpr int INFINITE = 1000000000;

struct Edge {
    int src, cost, dest;
    bool is_minimum, visited, is_minimum_path;

    void print() {
	printf("(src=%d, cost=%d, dest=%d, is_minimum=%d, is_minimum_path=%d)\n", src, cost, dest, is_minimum, is_minimum_path);
    }
};

typedef vector<vector<int> > AdjList;

static void
toposort(bool visited[MAX_NODES], const AdjList &adj_list, const vector<Edge> &edges, vector<int> &toposorted, int &index, int node) {
    visited[node] = true;
    int sz = adj_list[node].size();
    for(int i=0; i<sz; i++) {
	int n = edges[adj_list[node][i]].dest;
	if(!visited[n])
	    toposort(visited, adj_list, edges, toposorted, index, n);
    }
    toposorted[index] = node;
    index--;
}

static void
DFS(bool visited[MAX_NODES], const AdjList &adj_list, vector<Edge> &edges, int node) {
    visited[node] = true;
    int sz = adj_list[node].size();
    for(int i=0; i<sz; i++) {
	int n = edges[adj_list[node][i]].dest;
	edges[adj_list[node][i]].is_minimum_path = edges[adj_list[node][i]].is_minimum;
	if(!visited[n] && edges[adj_list[node][i]].is_minimum)
	    DFS(visited, adj_list, edges, n);
    }
}

static int
count_minimum_path(const vector<Edge> &edges, const AdjList &adj_list, int node) {
    int count = 0;
    for(auto i=adj_list[node].begin(); i != adj_list[node].end(); i++) {
	if(edges[*i].is_minimum_path)
	    count++;
    }
    return count;
}

static int
number_ones_in_mask(int mask) {
    int n = 0;
    for(int i=0; i<MAX_NODES; i++)
	if(mask & (1 << i))
	    n++;
    return n;
}

int
main() {
    AdjList adj_list;
    vector<Edge> edges;
    vector<int> toposorted; // topologically sorted node indices

    vector<int> node_cost;

    adj_list.reserve(MAX_NODES);
    toposorted.reserve(MAX_NODES);
    edges.reserve(MAX_NODES*(MAX_NODES+1) / 2);
    node_cost.reserve(MAX_NODES);

    int N_nodes;
    while(scanf("%d", &N_nodes) && N_nodes) {
	// parse input
	adj_list.resize(N_nodes);
	edges.clear();
	for(int i=0; i<N_nodes; i++) {
	    char _node[2];
	    int N_tunnels;
	    scanf("%s %d", _node, &N_tunnels);
	    char node = _node[0] - 'A';
	    adj_list[node].resize(N_tunnels);
	    for(int j=0; j<N_tunnels; j++) {
		char c[2];
		int e_i = edges.size();
		edges.resize(e_i+1);
		scanf("%s %d", c, &edges[e_i].cost);
		edges[e_i].dest = c[0] - 'A';
		edges[e_i].src = node;
		edges[e_i].is_minimum = edges[e_i].is_minimum_path = false;
		edges[e_i].visited = false;
		adj_list[i][j] = e_i;
	    }
	}

	// topologically sort the DAG
	toposorted.resize(N_nodes);
	bool visited[MAX_NODES];
	fill(visited, visited+N_nodes, false);
	int index = N_nodes-1;
	toposort(visited, adj_list, edges, toposorted, index, 0);

	// get the minimum path cost, mark all edges that are their node's minimum
	node_cost.resize(N_nodes);
	node_cost[toposorted[N_nodes-1]] = 0;
	for(int i=N_nodes-2; i>=0; i--) {
	    int n = toposorted[i];
	    auto end = adj_list[n].end();
	    int mincost = INFINITE;
	    for(auto e_i = adj_list[n].begin(); e_i != end; e_i++) {
		int c = edges[*e_i].cost + node_cost[edges[*e_i].dest];
		mincost = (c < mincost ? c : mincost);
	    }
	    node_cost[n] = mincost;
	    for(auto e_i = adj_list[n].begin(); e_i != end; e_i++) {
		if(edges[*e_i].cost + node_cost[edges[*e_i].dest] == mincost)
		    edges[*e_i].is_minimum = true;
	    }
	}

	/* for(int i=0; i<node_cost.size(); i++)
	    printf("%d: %d\n", toposorted[i], node_cost[toposorted[i]]);
	for(int i=0; i<edges.size(); i++)
	    edges[i].print();
	puts("\n"); */

	// Generate the minimum paths: minimum edges accessible from root
	fill(visited, visited+N_nodes, false);
	DFS(visited, adj_list, edges, 0);

	
	// assume MAX_NODES < 31
	vector<pair<int, int>> marked_children(N_nodes, make_pair(0, 0x0)); // (mask with the marked children, number of marked children)
	for(int i=N_nodes-2; i>=0; i--) {
	    int n = toposorted[i];
	    int mask_no_mark = 0;
	    int num_marks_if_no_mark = INFINITE;
	    if(adj_list[n].size() == count_minimum_path(edges, adj_list, n)) {
		for(int j=0; j<adj_list[n].size(); j++) {
		    if(!edges[adj_list[n][j]].is_minimum_path)
			continue;
		    mask_no_mark |= marked_children[edges[adj_list[n][j]].dest].second;
		}
		num_marks_if_no_mark = number_ones_in_mask(mask_no_mark);
	    }

	    int num_marks_if_mark = INFINITE;
	    int mask_mark;
	    for(int j=0; j<adj_list[n].size(); j++) {
		if(!edges[adj_list[n][j]].is_minimum_path)
		    continue;
		auto p = marked_children[edges[adj_list[n][j]].dest];
		if(p.first < num_marks_if_mark) {
		    num_marks_if_mark = p.first;
		    mask_mark = p.second;
		}
	    }
	    num_marks_if_mark += 1;
	    mask_mark |= 1 << n;

	    if(num_marks_if_mark < num_marks_if_no_mark) {
		marked_children[n].first = num_marks_if_mark;
		marked_children[n].second = mask_mark;
	    } else {
		marked_children[n].first = num_marks_if_no_mark;
		marked_children[n].second = mask_no_mark;
	    }
	}

	// finally, print out the results
	printf("%d %d\n", node_cost[toposorted[0]], marked_children[toposorted[0]].first);
    }
    return 0;
}
