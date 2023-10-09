#ifndef GEOMETRY_POINT_HPP
#define GEOMETRY_POINT_HPP

template<typename T>
struct point {
    T x, y;
    point() : x(0), y(0) {}

    explicit point(const T &_x, const T &_y = 0) : x(_x), y(_y) {}

    template<typename S>
    point(const point<S> &other) : x(other.x), y(other.y) {}
};

template<typename T> using vec = point<T>;

template<typename T>
int quadrant(const T &x, const T &y) {
    if (x == 0 && y == 0) return 0;
    if (x >  0 && y >= 0) return 1;
    if (x <= 0 && y >  0) return 2;
    if (x <  0 && y <= 0) return 3;
    if (x >= 0 && y <  0) return 4;
    assert(false);
}

template<typename T>
int quadrant(const point<T> &p) { return quadrant(p.x, p.y); }

template<typename T>
T cross(const T &x1, const T &y1, const T &x2, const T &y2) { return (lll) x1 * y2 - y1 * x2; }

template<typename T>
T cross(const vec<T> &p1, const vec<T> &p2) { return cross(p1.x, p1.y, p2.x, p2.y); }

#endif // GEOMETRY_POINT_HPP