#include "point.h"
#include <cmath>

double to_radians(double degrees)
{
    return M_PI / 180 * degrees;
}

void point::translate(const vec &vec)
{
    x += vec.dx;
    y += vec.dy;
}

void point::rotate(const point &origin, double angle)
{
    angle = to_radians(angle);
    double x_new = x - origin.x;
    double y_new = y - origin.y;
    x = x_new * cos(angle) - y_new * sin(angle);
    y = x_new * sin(angle) + y_new * cos(angle);
    x += origin.x;
    y += origin.y;
}

void point::symmetry_center(const point &center)
{
    x = 2 * center.x - x;
    y = 2 * center.y - y;
}

void point::symmetry_x()
{
    y = -y;
}

void point::symmetry_y()
{
    x = -x;
}

void point::symmetry_line(const line &l)
{
    double d = (l.a * x + l.b * y + l.c) / (l.a * l.a + l.b * l.b);
    x = x - 2 * d * l.a;
    y = y - 2 * d * l.b;
}

double points_distance(const point &p1, const point &p2)
{
    double first = (p2.x - p1.x) * (p2.x - p1.x);
    double second = (p2.y - p1.y) * (p2.y - p1.y);
    return sqrt(first + second);
}