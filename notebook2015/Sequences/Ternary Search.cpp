double E = 0.0000001; // tolerance
double L = 200000; // R and L are extreme possible values... 
double R = -200000; // ... for the optimized parameter
while (1) {
    double dist = R - L;
    if (fabs(dist) < E) break;
    double leftThird = L + dist / 3;
    double rightThird = R - dist / 3;
    // f is the function which we are optimizing
    if (f(leftThird) < f(rightThird))
        R = rightThird;
    else
        L = leftThird;
}
