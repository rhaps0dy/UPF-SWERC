typedef double T; // dejar incluso cuando puntos son int

class Point {
public:
    T x, y; // punto definido por coordinado (x,y)
    Point() { x = DBL_MAX; y = DBL_MAX; }
    Point(T a, T b) { x = a; y = b; }
    double distance(Point p) { // distancia entre dos puntos
        return sqrt(SQ(p.x - x) + SQ(p.y - y));
    }
};

class Line {
public:
    Point p, q; // linea definida por dos puntos DIFERENTES
    Line(Point a, Point b) { p = a; q = b; }
    double distance(Point r) { // distancia de linea a punto
        return r.distance(projection(r));
    }
    // projeccion de punto sobre linea
    Point projection(Point r) {
        if (p.y == q.y)
            return isect(Line(r, Point(r.x, r.y + 1)));
        T z = (q.x - p.x)/(q.y - p.y);
        return isect(Line(r, Point(r.x + 1,r.y - z)));
    }
    Point isect(Line l) { // interseccion entre dos lineas
        if (p.x == q.x) {
            if (l.p.x == l.q.x) // lineas son paralelas
                return Point();
            double a = (l.q.y - l.p.y)/(l.q.x - l.p.x);
            return Point(p.x, l.p.y + a*(p.x - l.p.x));
        }
        else if (l.p.x == l.q.x)
            return l.isect(*this);
        double a1 = (q.y - p.y)/(q.x - p.x);
        double a2 = (l.q.y - l.p.y)/(l.q.x - l.p.x);
        if (a1 == a2) // lines are parallel
            return Point();
        double x = (l.p.y - p.y + p.x*a1 - l.p.x*a2)/(a1-a2);
        return Point(x, p.y + (x - p.x)*a1);
    }
};

class Circle {
public:
    Point p; // punto central del circulo
    T r;     // radio del circulo
    Circle(Point a, T b) { p = a; r = b; }
    bool contains(Point q) { // punto dentro del circulo
        return p.distance(q) <= r;
    }
    // UNA interseccion entre linea and circulo
    Point isect(Line l) {
        Point q = l.projection(p);
        double d = p.distance(q);
        if (d > r) // la linea no intersecta el circulo
            return Point();
        if (l.p.x == l.q.x) {
            double dy = sqrt(SQ(r) - SQ(d));
            return Point(q.x, q.y + dy);
            // otro punto se obtiene por q.y - dy
        }
        double a = (l.q.y - l.p.y)/(l.q.x - l.p.x);
        double x = q.x - p.x;
        double y = q.y - p.y;
        double n = SQ(a) + 1;
        double s = sqrt((SQ(r) - SQ(d))/n);
        double dx = (x + a*y)/n + s;
        // otro punto se obtiene por (x + a*y)/n - s
        return Point(q.x + dx, q.y + a*dx);
    }
};

class Rect {
public:
    Point p, q; // rect definido por dos puntos DIFERENTES
    Rect(Point a, Point b) {
        p = Point(min(a.x, b.x), min(a.y, b.y));
        q = Point(max(a.x, b.x), max(a.y, b.y));
    }
    bool contains(Point r) { // punto dentro del rect
        return r.x>=p.x && r.x<=q.x && r.y>=p.y && r.y<=q.y;
    }
    // UNA interseccion entre rectangulo y linea
    Point isect(Line l) {
        Point r = l.isect(Line(p, Point(q.x, p.y)));
        if (r.x >= p.x && r.x <= q.x)
            return r;
        r = l.isect(Line(p, Point(p.x, q.y)));
        if (r.y >= p.y && r.y <= q.y)
            return r;
        r = l.isect(Line(Point(q.x, p.y), q));
        if (r.y >= p.y && r.y <= q.y)
            return r;
        r = l.isect(Line(Point(p.x, q.y), q));
        if (r.x >= p.x && r.x <= q.x)
            return r;
        return Point();
    }
    // UNA interseccion entre rectangulo y circulo
    Point isect(Circle c) {
        Point r = c.isect(Line(p, Point(q.x, p.y)));
        if (r.x >= p.x && r.x <= q.x)
            return r;
        r = c.isect(Line(p, Point(p.x, q.y)));
        if (r.y >= p.y && r.y <= q.y)
            return r;
        r = c.isect(Line(Point(q.x, p.y), q));
        if (r.y >= p.y && r.y <= q.y)
            return r;
        r = c.isect(Line(Point(p.x, q.y), q));
        if (r.x >= p.x && r.x <= q.x)
            return r;
        return Point();
    }
};

int main() {
    Point p(0, 0);
    Point q(2, 2);
    Point s(0, 2);
    Line l(p, q);
    Circle c(s, 2);
    Rect r(p, q);
    Point t = c.isect(l);
    Point u = r.isect(c);
}