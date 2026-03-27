#include "point.h"
#include "segment.h"
#include "triangle.h"
#include "vec.h"
#include <iostream>

using namespace std;

void print_point(const string &label, const point &p)
{
    cout << label;
    cout << "{" << p.x << ", " << p.y << "}" << '\n';
}

void print_segment(const string &label, Segment &seg)
{
    cout << label;
    const point a = seg.get_P1();
    const point b = seg.get_P2();
    cout << "{A: {" << a.x << ", " << a.y << "}, ";
    cout << "B: {" << b.x << ", " << b.y << "}}\n";
}

void print_triangle(const string &label, Triangle &tri)
{
    cout << label;
    const point a = tri.get_P1();
    const point b = tri.get_P2();
    const point c = tri.get_P3();
    cout << "{A: {" << a.x << ", " << a.y << "}, ";
    cout << "B: {" << b.x << ", " << b.y << "}, ";
    cout << "C: {" << c.x << ", " << c.y << "}}\n";
}

void test_point(vec &v, line &l)
{
    cout << "TEST OF POINT.H\n";
    point p1 = {1, 1};
    point p2 = {-5, -6};
    print_point("point p1:", p1);
    print_point("point p2: ", p2);
    cout << '\n';
    
    // TRANSLATION
    point p1_copy = p1;
    p1_copy.translate(v);
    print_point("Translation of p1 by v: ", p1_copy);

    // ROTATION
    p1_copy = p1;
    p1_copy.rotate({0, 0}, 90);
    print_point("Rotation of p1 by 90 degrees around the origin (0, 0): ", p1_copy);
    p1_copy = p1;
    p1_copy.rotate(p2, 180);
    print_point("Rotation of p1 by 180 degrees around p2: ", p1_copy);

    // CENTRAL SYMMETRY
    p1_copy = p1;
    p1_copy.symmetry_center(p2);
    print_point("Central symmetry of p1 with respect to p2: ", p1_copy);

    // X-SYMMETRY
    p1_copy = p1;
    p1_copy.symmetry_x();
    print_point("Reflection of p1 across the X-axis: ", p1_copy);

    // Y-SYMMETRY
    p1_copy = p1;
    p1_copy.symmetry_y();
    print_point("Reflection of p1 across the Y-axis: ", p1_copy);

    // LINE SYMMETRY
    p1_copy = p1;
    p1_copy.symmetry_line(l);
    print_point("Reflection of p1 across l: ", p1_copy);

    // DISTANCE
    cout << "Distance between p1 and p2: " << points_distance(p1, p2) << '\n';
}

void test_segment(vec &v, line &l)
{
    cout << "TEST OF SEGMENT.H\n";
    Segment seg1({1, 1}, {3, 4});
    Segment seg2({5, 1}, {7, 4});
    Segment seg3({1, 1}, {-2, 3});
    print_segment("Segment seg1: ", seg1);
    print_segment("Segment seg2: ", seg2);
    print_segment("Segment seg3: ", seg3);
    cout << '\n';

    // CONSTRUCTING SEGMENT WITH IDENTICAL ENDPOINTS
    cout << "Constructing segment with identical endpoints:\n";
    try
    {
        Segment invalid_seg({0, 0}, {0, 0});
    }
    catch (const exception &e)
    {
        cout << e.what() << "\n\n";
    }

    // COPY CONSTRUCTOR
    Segment seg1_copy(seg1);
    print_segment("Copy of seg1: ", seg1_copy);

    // COPY ASSIGNMENT
    seg1_copy = seg1;
    print_segment("Copy assignment of seg1: ", seg1_copy);

    // TRANSLATION
    seg1_copy.segment_translate(v);
    print_segment("Translation of seg1 by v: ", seg1_copy);

    // ROTATION
    seg1_copy = seg1;
    seg1_copy.segment_rotate({0, 0}, 90);
    print_segment("Rotation of seg1 by 90 degrees around the origin (0, 0): ", seg1_copy);
    seg1_copy = seg1;
    seg1_copy.segment_rotate({2, 5}, 180);
    print_segment("Rotation of seg1 by 180 degrees around (2, 5): ", seg1_copy);

    // CENTRAL SYMMETRY
    seg1_copy = seg1;
    seg1_copy.segment_symmetry_center({0, 0});
    print_segment("Central symmetry of seg1 with respect to (0, 0): ", seg1_copy);

    // X-SYMMETRY
    seg1_copy = seg1;
    seg1_copy.segment_symmetry_x();
    print_segment("Reflection of seg1 across the X-axis: ", seg1_copy);

    // Y-SYMMETRY
    seg1_copy = seg1;
    seg1_copy.segment_symmetry_y();
    print_segment("Reflection of seg1 across the Y-axis: ", seg1_copy);

    // LINE SYMMETRY
    seg1_copy = seg1;
    seg1_copy.segment_symmetry_line(l);
    print_segment("Reflection of seg1 across l: ", seg1_copy);

    // SEGMENT LENGTH
    cout << "Length of seg1: " << seg1.segment_length() << "\n\n";

    // POINT IN SEGMENT
    cout << "Check if point (1, 1) is in seg1: " << seg1.point_in_segment({1, 1}) << '\n';
    cout << "Check if point (8, 10) is in seg1: " << seg1.point_in_segment({8, 10}) << "\n\n";

    // PARALLELISM
    cout << "Check if seg2 is parallel to seg1: " << are_parallel(seg1, seg2) << "\n\n";

    // PERPENDICULARITY
    cout << "Check if seg2 is perpendicular to seg1: " << are_perpendicular(seg1, seg2) << '\n';
    cout << "Check if seg3 is perpendicular to seg1: " << are_perpendicular(seg1, seg3) << "\n\n";

    // INTERSECTION
    cout << "Check if seg1 and seg2 intersect: " << intersect(seg1, seg2) << '\n';
}

void test_triangle(vec &v, line &l)
{
    cout << "TEST OF TRIANGLE.H\n";
    Triangle tri1({1,1}, {5, 1}, {3, 4});
    Triangle tri2({2, 1.5}, {4, 1.5}, {3, 2.5});
    Triangle tri3({-5, -10}, {-9, -3}, {-20, -6});
    print_triangle("Triangle tri1: ", tri1);
    print_triangle("Triangle tri2: ", tri2);
    print_triangle("Triangle tri3: ", tri3);
    cout << '\n';

    // CONSTRUCTING TRIANGLE WITH IDENTICAL VERTICES
    cout << "Constructing triangle with identical vertices:\n";
    try
    {
        Triangle invalid_tri({0, 0}, {0, 0}, {0, 0});
    }
    catch (const exception &e)
    {
        cout << e.what() << "\n\n";
    }

    // CONSTRUCTING TRIANGLE WITH COLLINEAR VERTICES
    cout << "Constructing triangle with collinear vertices:\n";
    try
    {
        Triangle invalid_tri({0, 0}, {5, 0}, {-5, 0});
    }
    catch (const exception &e)
    {
        cout << e.what() << "\n\n";
    }

    // COPY CONSTRUCTOR
    Triangle tri1_copy(tri1);
    print_triangle("Copy of tri1: ", tri1_copy);

    // COPY ASSIGNMENT
    tri1_copy = tri1;
    print_triangle("Copy assignment of tri1: ", tri1_copy);

    // TRANSLATION
    tri1_copy.triangle_translate(v);
    print_triangle("Translation of tri1 by v: ", tri1_copy);

    // ROTATION
    tri1_copy = tri1;
    tri1_copy.triangle_rotate({0, 0}, 90);
    print_triangle("Rotation of tri1 by 90 degrees around the origin (0, 0): ", tri1_copy);
    tri1_copy = tri1;
    tri1_copy.triangle_rotate({2, 5}, 180);
    print_triangle("Rotation of tri1 by 180 degrees around (2, 5): ", tri1_copy);

    // CENTRAL SYMMETRY
    tri1_copy = tri1;
    tri1_copy.triangle_symmetry_center({0, 0});
    print_triangle("Central symmetry of tri1 with respect to (0, 0): ", tri1_copy);

    // X-SYMMETRY
    tri1_copy = tri1;
    tri1_copy.triangle_symmetry_x();
    print_triangle("Reflection of tri1 across the X-axis: ", tri1_copy);

    // Y-SYMMETRY
    tri1_copy = tri1;
    tri1_copy.triangle_symmetry_y();
    print_triangle("Reflection of tri1 across the Y-axis: ", tri1_copy);

    // LINE SYMMETRY
    tri1_copy = tri1;
    tri1_copy.triangle_symmetry_line(l);
    print_triangle("Reflection of tri1 across l: ", tri1_copy);

    // PERIMETER
    cout << "Perimeter of tri1: " << tri1.get_perimeter() << '\n';

    // AREA
    cout << "Area of tri1: " << tri1.get_area() << "\n\n";

    // POINT IN TRIANGLE
    cout << "Check if point (1, 1) is in tri1: " << tri1.point_in_triangle({1, 1}) << '\n';
    cout << "Check if point (8, 10) is in tri1: " << tri1.point_in_triangle({8, 10}) << "\n\n";

    // DISJOINT TRIANGLES
    cout << "Check if tri1 and tri2 are disjoint: " << are_disjoint(tri1, tri2) << '\n';
    cout << "Check if tri1 and tri3 are disjoint: " << are_disjoint(tri1, tri3) << "\n\n";

    // CONTAINMENT
    cout << "Check if tri1 is contained in tri2: " << is_contained(tri1, tri2) << '\n';
    cout << "Check if tri2 is contained in tri1: " << is_contained(tri2, tri1) << '\n';
}

void test_pod()
{
    cout << "POD TEST\n";
    cout << (is_trivial<point>::value && is_standard_layout<point>::value ? "POINT IS POD\n" : "POINT IS NOT POD\n");

    cout << (is_trivial<vec>::value && is_standard_layout<vec>::value ? "VEC IS POD\n" : "VEC IS NOT POD\n");

    cout << (is_trivial<line>::value && is_standard_layout<line>::value ? "LINE IS POD\n" : "LINE IS NOT POD\n");

    cout << (is_trivial<Segment>::value && is_standard_layout<Segment>::value ? "SEGMENT IS POD\n" : "SEGMENT IS NOT POD\n");

    cout << (is_trivial<Triangle>::value && is_standard_layout<Triangle>::value ? "TRIANGLE IS POD\n" : "TRIANGLE IS NOT POD\n");
}

int main()
{
    vec v = {2, 2};
    line l = {1, 2, 3};
    cout << "vec v: " << "[" << v.dx << ", " << v.dy << "]" << "\n";
    cout << "line l: " << l.a << " * x + " << l.b << " * y + " << l.c << " = 0" << "\n\n";

    test_point(v, l);
    cout << "\n\n";
    test_segment(v, l);
    cout << "\n\n";
    test_triangle(v, l);
    cout << "\n\n";
    test_pod();
    return 0;
}