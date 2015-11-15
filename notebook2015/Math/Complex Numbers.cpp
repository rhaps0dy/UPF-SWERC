// Complex number class, from Stanford's Notebook. Required for FFT
struct cpx {
    cpx(){}
    cpx(double aa):a(aa){}
    cpx(double aa, double bb):a(aa),b(bb){}
    double a, b;
    double modsq(void) const { return a * a + b * b; }
    cpx bar(void) const { return cpx(a, -b); }
};
cpx operator +(cpx a, cpx b) { return cpx(a.a + b.a, a.b + b.b); }
cpx operator *(cpx a, cpx b) {
    return cpx(a.a * b.a - a.b * b.b, a.a * b.b + a.b * b.a);
}
cpx operator /(cpx a, cpx b) {
    cpx r = a * b.bar();
    return cpx(r.a / b.modsq(), r.b / b.modsq());
}
cpx EXP(double theta) { return cpx(cos(theta),sin(theta)); }
