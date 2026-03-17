#include "triangle.h"
#include <stdexcept>
#include <cmath>
#include "segment.h"
#define EPS 1e-6

using namespace std;

Triangle::Triangle()
{
    p1.x = 0;
    p1.y = 0;
    p2.x = 1;
    p2.y = 0;
    p3.x = 0;
    p3.y = 1;
}

Triangle::Triangle(const point &p1, const point &p2, const point &p3)
    : p1(p1), p2(p2), p3(p3)
{
    double dp1_p2 = points_distance(p1, p2);
    double dp1_p3 = points_distance(p1, p3);
    double dp2_p3 = points_distance(p2, p3);
    if (dp1_p2 < EPS || dp1_p3 < EPS || dp2_p3 < EPS)
    {
        throw invalid_argument("Triangle vertices cannot be identical!");
    }
    double cross = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    if (fabs(cross) < EPS) throw invalid_argument("Triangle vertices are collinear!");
}

Triangle::Triangle(const Triangle &other) : p1(other.p1), p2(other.p2), p3(other.p3)
{
}

Triangle& Triangle::operator=(const Triangle &other)
{
    if (this != &other)
    {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
    }
    return *this;
}

void Triangle::triangle_translate(const vec &vec)
{
    p1.translate(vec);
    p2.translate(vec);
    p3.translate(vec);
}

void Triangle::triangle_rotate(const point &origin, double angle)
{
    p1.rotate(origin, angle);
    p2.rotate(origin, angle);
    p3.rotate(origin, angle);
}

void Triangle::triangle_symmetry_center(const point &center)
{
    p1.symmetry_center(center);
    p2.symmetry_center(center);
    p3.symmetry_center(center);
}

void Triangle::triangle_symmetry_x()
{
    p1.symmetry_x();
    p2.symmetry_x();
    p3.symmetry_x();
}

void Triangle::triangle_symmetry_y()
{
    p1.symmetry_y();
    p2.symmetry_y();
    p3.symmetry_y();
}

void Triangle::triangle_symmetry_line(const line &l)
{
    p1.symmetry_line(l);
    p2.symmetry_line(l);
    p3.symmetry_line(l);
}

double Triangle::get_perimeter() const
{
    return points_distance(p1, p2) + points_distance(p2, p3) + points_distance(p3, p1);
}

double area(const point &p1, const point &p2, const point &p3)
{
    return fabs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0;
}

double Triangle::get_area() const
{
    return area(p1, p2, p3);
}

bool Triangle::point_in_triangle(const point &p) const
{
    Segment seg1(p1, p2);
    Segment seg2(p2, p3);
    Segment seg3(p3, p1);
    // Check if the point lies on any triangle edge
    if (seg1.point_in_segment(p) || seg2.point_in_segment(p) || seg3.point_in_segment(p))
        return true;
    // Check if the point is inside the triangle
    double whole = get_area();
    double a = area(p1, p, p3);
    double b = area(p3, p, p2);
    double c = area(p1, p, p2);
    return (fabs(whole - (a + b + c)) < EPS);
}

bool are_disjoint(const Triangle &tri1, const Triangle &tri2)
{
    const point &a = tri1.get_P1();
    const point &b = tri1.get_P2();
    const point &c = tri1.get_P3();
    const point &d = tri2.get_P1();
    const point &e = tri2.get_P2();
    const point &f = tri2.get_P3();

    // Check if any of the triangle edges intersect
    const Segment tri1_seg[] = {Segment(a, b), Segment(b, c), Segment(c, a)};
    const Segment tri2_seg[] = {Segment(d, e), Segment(e, f), Segment(f, d)};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (intersect(tri1_seg[i], tri2_seg[j])) return false;
        }
    }

    // Check if any vertex of one triangle lies inside the other triangle
    if (tri2.point_in_triangle(a) || tri2.point_in_triangle(b) || tri2.point_in_triangle(c))
        return false;
    if (tri1.point_in_triangle(d) || tri1.point_in_triangle(e) || tri1.point_in_triangle(f))
        return false;
    return true;
}

// Checks if the first triangle is entirely contained within the second
bool is_contained(const Triangle &tri1, const Triangle &tri2)
{
    const point &a = tri1.get_P1();
    const point &b = tri1.get_P2();
    const point &c = tri1.get_P3();
    return tri2.point_in_triangle(a) && tri2.point_in_triangle(b) && tri2.point_in_triangle(c);
}