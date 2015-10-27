/* Binary indexed tree. Supports cumulative sum queries in O(log n) */
#define N (1<<18)
LL bit[N];

void add(LL* bit,int x,int val) {
    for(; x<N; x+=x&-x)
        bit[x]+=val;
}

LL query(LL* bit,int x) {
    LL res=0;
    for(;x;x-=x&-x)
        res+=bit[x];
    return res;
}
