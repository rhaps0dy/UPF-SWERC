short W[1000][1000], M[1000][1000];
short wP[1001], mP[1001], coW[1001];
short listing[50000];
int N;

void stableMarriage(){
    int ac = 0, total = 0, ws, woman;
    for( int i = 0; i < N; i++ ){
        listing[total++] = i;
        coW[i] = 0;
    }

    while( ac < total ){
        ws = listing[ac++];
        if( wP[ws] != -1 )
            continue;

        for( ; coW[ws] < N; coW[ws]++ ){
            if (mP[ W[ws][ coW[ws] ] ] == -1 ) {
                wP[ws] = W[ws][ coW[ws] ];
                mP[ W[ws][ coW[ws] ] ] = ws;
                break;
            }
            else {
                woman = W[ws][ coW[ws] ];
                if( M[woman][ mP[woman] ] > M[woman][ws] ){
                    listing[total++] = mP[woman];
                    wP[ mP[woman] ] = -1;
                    mP[woman] = ws;
                    wP[ws] = woman;
                    break;
                }
            }
        }
    }
}
