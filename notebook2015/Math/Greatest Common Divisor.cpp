// in algorithm library: __gcd(a, b)
int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    else if (a%b == 0) return b;
    else return gcd(b, a%b);
}

gcd(a,b)*lcm(a,b) = a*b
