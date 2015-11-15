unsigned long long v[34];
void catalan(){
    v[0] = 1;
    for (int i = 1; i < 34; ++i){
        unsigned long long sum = 0;
        for (int j = 0; j < i; ++j){
            sum += v[j] * v[i-j-1];
        }
        v[i] = sum;
    }
}
