// O(n^2)

for(int i=0; i<N; i++) {
    inc[i] = 1;
    for(int j=0; j<N; j++) {
        if(seq[j] < seq[i]) {
            int v = inc[j] + 1;
            if(v > inc[i])
                inc[i] = v;
        }
    }
	if(inc[i] > max)
	    max = inc[i];
}

// O(n log n)

ind[0] = 0;
ind_sz = 1;
while(scanf("%d", &seq[seq_sz++]) == 1) {
    /*  Add next element if it's bigger than the current last */ 
    int i = seq_sz-1;
    if (seq[ind[ind_sz-1]] < seq[i]) {
        predecessor[i] = ind[ind_sz-1];
        ind[ind_sz++] = i;
        continue;
    }
    /*  bsearch to find element immediately bigger */
    int u = 0, v = ind_sz-1;
    while(u < v) {
        int c = (u + v) / 2;
        if (seq[ind[c]] < seq[i])
            u = c+1;
        else
            v = c;
    }
    /*  Update b if new value is smaller then previously referenced value  */
    if (seq[i] < seq[ind[u]]) {
        if (u > 0)
            predecessor[i] = ind[u-1];
        ind[u] = i;
    }
}
