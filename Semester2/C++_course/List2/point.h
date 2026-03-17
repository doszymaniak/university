#ifndef POINT_H
#define POINT_H

#include "vec.h"
#include "line.h"

struct point {
    double x;
    double y;

    void translate(const vec &vec);
    void rotate(const point &origin, double angle);
    void symmetry_center(const point &center);
    void symmetry_x();
    void symmetry_y();
    void symmetry_line(const line &l);
};

double points_distance(const point &p1, const point &p2);

#endif