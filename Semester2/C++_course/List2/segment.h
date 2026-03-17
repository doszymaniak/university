#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"
#include "vec.h"

class Segment {
private:
    struct point p1;
    struct point p2;
    
public:
    Segment();
    Segment(const point &p1, const point &p2);
    Segment(const Segment &other);
    Segment &operator=(const Segment &other);
    
    const point &get_P1() const { return p1; }
    const point &get_P2() const { return p2; }

    void segment_translate(const vec &vec);
    void segment_rotate(const point &origin, double angle);
    void segment_symmetry_center(const point &center);
    void segment_symmetry_x();
    void segment_symmetry_y();
    void segment_symmetry_line(const line &l);

    double segment_length();
    bool point_in_segment(const point &p) const;
};

bool are_parallel(const Segment &seg1, const Segment &seg2);
bool are_perpendicular(const Segment &seg1, const Segment &seg2);
bool intersect(const Segment &seg1, const Segment &seg2);

#endif