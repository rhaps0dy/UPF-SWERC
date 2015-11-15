vector<int> A[101]; // adjacency list (directed graph without cycles)
int inbound[101]; // number of nodes that point to each node
vector<int> fo; // final order

// M = number of nodes (there might be 'lonely' nodes)
void toposort(int M) {
    stack<int> order;
    int current;

    // Search for roots (identifiers might change between 
    // problems (e.g. 1 to M))
    for(int m = 0; m < M; m++){
        if(inbound[m] == 0)
            order.push(m);
    }

    // Start topsort from roots
    while(!order.empty()){
        // Pop from stack 
        current = order.top();
        order.pop();
        // Save order in fo
        fo.push_back(current);
        // Add childs only if inbound is 0
        for (int i = 0; i < A[current].size(); ++i)
        {
            inbound[A[current][i]]--;
            if (inbound[A[current][i]] == 0)
                order.push(A[current][i]);
        }
    }
}

int main() {
    A[0].push_back(1); A[0].push_back(2); A[2].push_back(1);
    inbound[0] = 0; inbound[1] = 2; inbound[2] = 1;
    toposort(3);
    for (int i = 0; i < fo.size(); ++i) cout << fo[i] << " ";
    // 0 2 1
}
