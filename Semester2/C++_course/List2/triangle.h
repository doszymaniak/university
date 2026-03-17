#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "vec.h"

class Triangle {
private:
    struct point p1;
    struct point p2;
    struct point p3;

public:
    Triangle();
    Triangle(const point &p1, const point &p2, const point &p3);
    Triangle(const Triangle &other);
    Triangle &operator=(const Triangle &other);

    void triangle_translate(const vec &vec);
    void triangle_rotate(const point &origin, double angle);
    void triangle_symmetry_center(const point &center);
    void triangle_symmetry_x();
    void triangle_symmetry_y();
    void triangle_symmetry_line(const line &l);

    const point &get_P1() const { return p1; }
    const point &get_P2() const { return p2; }
    const point &get_P3() const { return p3; }

    double get_perimeter() const;
    double get_area() const;
    bool point_in_triangle(const struct point &p) const;
};

bool are_disjoint(const Triangle &tri1, const Triangle &tri2);
bool is_contained(const Triangle &tri1, const Triangle &tri2);

#endif