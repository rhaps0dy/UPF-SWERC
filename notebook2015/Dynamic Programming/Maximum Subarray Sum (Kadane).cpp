/* We show the 2D version here. the 1D version is the code block
separated by a newline. You can keep track of where the sequence
starts and ends by messing with the max_here and max assignments
respectively. Use > max_here to keep longer subsequences, >= max_here
to keep shorter ones. Take into account circular arrays by adding the
sum of all elements and the max of the array with sign changed.  */
max = mat[0][0];
for(i=0; i<N; i++) {
    memset(aux, 0, sizeof(aux));
    for(k=i; k<N; k++) {
        for(j=0; j<N; j++)
            aux[j] += mat[k][j];

        max_here = aux[0];
        if(max_here > max)
            max = max_here;
        for(j=1; j<N; j++) {
            max_here += aux[j];
            if(aux[j] > max_here)
                max_here = aux[j];
            if(max_here > max)
                max = max_here;
        }
    }
}
