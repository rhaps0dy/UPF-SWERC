#include <cstdio>
#include <vector>
#include <utility>
#include <cstring>

#define PB push_back

using namespace std;

constexpr int MAX_WIDTH = 7;
// there are more MAX_NODES than maximum possible nodes but meh
constexpr int MAX_NODES = MAX_WIDTH * (MAX_WIDTH + 1);

char nodes[MAX_NODES+1];
vector<vector<int> > adj_list;
bool visited[MAX_NODES+1];

char solution[MAX_NODES+1];
int solution_len;

int target_first, target_last, pattern_length;

int first_bottom_row_node;

static void
DFS(int cur, int depth, bool has_been_bottom) {
	static char str_so_far[MAX_NODES+1];
	str_so_far[depth] = nodes[cur];

	if(cur >= target_first && cur <= target_last && has_been_bottom &&
	   depth % pattern_length == pattern_length-1 && nodes[cur] == str_so_far[pattern_length-1]) {
		int len = depth+1;
		if(len < solution_len) {
			solution_len = len;
			str_so_far[len] = '\0';
			strcpy(solution, str_so_far);
		}
	}

	bool is_bottom = cur >= first_bottom_row_node;

	visited[cur] = true;
	for(int i=0; i<adj_list[cur].size(); i++) {
		int n = adj_list[cur][i];
		if(!visited[n] && (depth < pattern_length || str_so_far[depth % pattern_length] == nodes[cur]))
			DFS(n, depth+1, is_bottom || has_been_bottom);
	}
	visited[cur] = false;
}


int main() {
	adj_list.reserve(MAX_NODES);
	int r, c, n;

	while(scanf("%d", &r) && r) {
		scanf("%d %d", &c, &pattern_length);
		adj_list.resize(r/2 * (c + 1) + (r/2 + r%2) * c);
		first_bottom_row_node = adj_list.size() - (r%2 ? c : c+1);

		// Generate hex grid
		int cur_node = 0;
		for(int j=0; j<r; j++) {
			for(int i=0; (j%2 ? i<c+1 : i<c); i++) {
				adj_list[cur_node].clear();
				if(j % 2) {
					if(i != c) {
						// add top-right, bottom-right and right
						adj_list[cur_node].PB(cur_node - c);
						if(j != r-1)
							adj_list[cur_node].PB(cur_node + c+1);
						adj_list[cur_node].PB(cur_node + 1);
					}
					if(i != 0) {
						// add top-left, bottom-left and left
						adj_list[cur_node].PB(cur_node - (c + 1));
						if(j != r-1)
							adj_list[cur_node].PB(cur_node + c);
						adj_list[cur_node].PB(cur_node - 1);
					}
				} else {
					if(i != 0) {
						adj_list[cur_node].PB(cur_node - 1);
					}
					if(i != c-1) {
						adj_list[cur_node].PB(cur_node + 1);
					}
					if(j != r - 1) {
						// add the two bottom
						adj_list[cur_node].PB(cur_node + c);
						adj_list[cur_node].PB(cur_node + c + 1);
					}
					if(j != 0) {
						// add the two top
						adj_list[cur_node].PB(cur_node - c);
						adj_list[cur_node].PB(cur_node - (c + 1));
					}
				}

				cur_node++;
			}
		}

		// Get letters of each node
		for(int i=0; i<adj_list.size(); i++)
			scanf("%s", nodes+i);

		solution_len = 100000;
		target_last = c-1;

		for(int i=0; i<c-1; i++) {
			fill(visited, visited+adj_list.size(), false);
			target_first = i+1;
			DFS(i, 0, false);
		}

		if(solution_len == 100000)
			puts("no solution");
		else
			puts(solution);
	}
	return 0;
}
