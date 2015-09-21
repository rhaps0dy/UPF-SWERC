#include <cstdio>
#include <cmath>

typedef long long INT;

INT gcd(INT a, INT b) {
    if(a < b) return gcd(b, a);
    if(a % b == 0) return b;
    return gcd(b, a%b);
}

struct Rational {
    INT num, den;

    void print() { printf("%lld/%lld", num, den); }

    Rational(INT _num, INT _den) {
        num = _num;
        den = _den;
        simplify();
    }
    
    double toDouble() const {
        return ((double)num) / ((double)den);
    }
    Rational operator-(Rational b) const {
        Rational c(num * b.den - b.num * den, den*b.den);
        c.simplify();
        return c;
    }
    Rational operator/(Rational b) const {
        if(b.num == 0) {
            printf("Tried to divide %lld/%lld by %lld/%lld\n", num, den, b.num, b.den);
        }
        Rational c(num*b.den, den*b.num);
        c.simplify();
        return c;
    }
    Rational operator*(Rational b) const {
        b.num *= num;
        b.den *= den;
        b.simplify();
        return b;
    }
    Rational operator+(Rational b) const {
        Rational c(num * b.den + b.num * den, den*b.den);
        c.simplify();
        return c;
    }
     
    void simplify() {
        if(den < 0) {
            num = -num;
            den = -den;
        }
        if(num == 0) {
            den = 1;
            return;
        }
        INT d = gcd(std::abs(num), den);
        if(d != 0) {
            num /= d;
            den /= d;
        }
    }
};

int
main() 
{

    int ax, bx, cx, ay, by, cy;
    Rational half(1, 2);

    while(scanf("%d %d %d %d %d %d", &ax, &ay, &bx, &by, &cx, &cy) == 6) {
//        printf("%5d %5d %5d %5d %5d %5d | ", ax, ay, bx, by, cx, cy);
        int abx, aby, acx, acy;
        abx = bx - ax;
        aby = by - ay;
        acx = cx - ax;
        acy = cy - ay;

        // test for collinearity
        if((abx == 0 && acx == 0) ||
           (aby == 0 && acy == 0) ||
           (abx * acy == acx * aby)) {
            puts("Impossible");
            continue;
        }
        Rational
            Px(ax+bx, 2),
            Py(ay+by, 2),
            Qx(ax+cx, 2),
            Qy(ay+cy, 2),
            px(-aby, 1),
            py(abx, 1),
            qx(-acy, 1),
            qy(acx, 1);

        Rational s(0, 1);
        if(py.num == 0) {
            Rational py_px = py / px;
            s = (Py + py_px*(Qx - Px) - Qy) / (qy - py_px*qx);
        } else {
            Rational px_py = px / py;
/*            putchar('\n');
            printf("px: ");
            px.print();
            printf(" py: ");
            py.print();
            printf(" px/py: ");
            px_py.print();
            putchar('\n');
            printf("Qy - Py = ");
            (Qy - Py).print();
            printf("\npx/py*(Qy - Py) = ");
            (px_py*(Qy - Py)).print();
            printf("\nPx + px/py*(Qy - Py) - Qx = ");
            (Px + px_py*(Qy - Py) - Qx).print();
            putchar('\n'); */
            s = (Px + px_py*(Qy - Py) - Qx) / (qx - px_py*qy);
//            s.print();
        }
        Rational
            x = Qx + qx * s,
            y = Qy + qy * s;
        printf("%lf %lf\n", x.toDouble(), y.toDouble());
/*        double xx = x.toDouble(), yy = y.toDouble();
#define norm(a, b, c, d) (d-b)*(d-b) + (c-a)*(c-a)
        double na = norm(xx, yy, (double)ax, (double)ay);
        double nb = norm(xx, yy, (double)bx, (double)by);
        double nc = norm(xx, yy, (double)cx, (double)cy);
#undef norm
    printf("%lf %lf %lf\n", std::fabs(na-nb), std::fabs(nb-nc), std::fabs(nc-na)); */
    }
    return 0;
}
