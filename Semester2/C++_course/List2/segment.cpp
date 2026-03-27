#include "segment.h"
#include <stdexcept>
#include <math.h>
#define EPS 1e-9

using namespace std;

Segment::Segment()
{
    p1.x = 0;
    p1.y = 0;
    p2.x = 10;
    p2.y = 0;
}

Segment::Segment(const point &first, const point &second) : p1(first), p2(second)
{
    if (first.x == second.x && first.y == second.y)
    {
        throw invalid_argument("Segment endpoints cannot be identical!");
    }
}

Segment::Segment(const Segment &other) : p1(other.p1), p2(other.p2)
{
}

Segment& Segment::operator=(const Segment &other)
{
    if (this != &other)
    {
        p1 = other.p1;
        p2 = other.p2;
    }
    return *this;
}

void Segment::segment_translate(const vec &vec)
{
    p1.translate(vec);
    p2.translate(vec);
}

void Segment::segment_rotate(const point &origin, double angle)
{
    p1.rotate(origin, angle);
    p2.rotate(origin, angle);
}

void Segment::segment_symmetry_center(const point &center)
{
    p1.symmetry_center(center);
    p2.symmetry_center(center);
}

void Segment::segment_symmetry_x()
{
    p1.symmetry_x();
    p2.symmetry_x();
}

void Segment::segment_symmetry_y()
{
    p1.symmetry_y();
    p2.symmetry_y();
}

void Segment::segment_symmetry_line(const line &l)
{
    p1.symmetry_line(l);
    p2.symmetry_line(l);
}

double Segment::segment_length()
{
    return points_distance(p1, p2);
}

double cross(const point &p1, const point &p2, const point &p3)
{
    double cross = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    return cross;
}

bool Segment::point_in_segment(const point &p) const
{
    // Collinearity check
    if (fabs(cross(p1, p2, p)) > EPS) return false;
    // Check if the point lies between the segment endpoints
    return p.x >= min(p1.x, p2.x) && p.x <= max(p1.x, p2.x) && p.y >= min(p1.y, p2.y) && p.y <= max(p1.y, p2.y);
}

bool are_parallel(const Segment &seg1, const Segment &seg2)
{
    const point &a = seg1.get_P1();
    const point &b = seg1.get_P2();
    const point &c = seg2.get_P1();
    const point &d = seg2.get_P2();
    double dx1 = b.x - a.x;
    double dy1 = b.y - a.y;
    double dx2 = d.x - c.x;
    double dy2 = d.y - c.y;
    double cross = dx1 * dy2 - dy1 * dx2;
    return fabs(cross) < EPS;
}

bool are_perpendicular(const Segment &seg1, const Segment &seg2)
{
    const point &a = seg1.get_P1();
    const point &b = seg1.get_P2();
    const point &c = seg2.get_P1();
    const point &d = seg2.get_P2();
    double dx1 = b.x - a.x;
    double dy1 = b.y - a.y;
    double dx2 = d.x - c.x;
    double dy2 = d.y - c.y;
    double dot = dx1 * dx2 + dy1 * dy2;
    return fabs(dot) < EPS;
}

bool intersect(const Segment &seg1, const Segment &seg2)
{
    const point &a = seg1.get_P1();
    const point &b = seg1.get_P2();
    const point &c = seg2.get_P1();
    const point &d = seg2.get_P2();
    double v1 = cross(c, d, a);
    double v2 = cross(c, d, b);
    double v3 = cross(a, b, c);
    double v4 = cross(a, b, d);
    // Check for standard intersection
    if (((v1 > EPS && v2 < -EPS) || (v1 < -EPS && v2 > EPS)) && ((v3 > EPS && v4 < -EPS) || (v3 < -EPS && v4 > EPS))) return 1;
    // Check cases where an endpoint of one segment lies exactly on the other segment
    if (fabs(v1) < EPS && seg2.point_in_segment(a)) return 1;
    if (fabs(v2) < EPS && seg2.point_in_segment(b)) return 1;
    if (fabs(v3) < EPS && seg1.point_in_segment(c)) return 1;
    if (fabs(v4) < EPS && seg1.point_in_segment(d)) return 1;
    return 0;
}