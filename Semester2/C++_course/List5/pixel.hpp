#ifndef PIXEL_HPP
#define PIXEL_HPP

class Pixel {
private:
    int x;
    int y;
    static const int disp_x = 800;
    static const int disp_y = 600;
public:
    void check_coordinates(int x, int y);
    Pixel(int x, int y);
    int get_x() const;
    int get_y() const;
    void set_x(int x);
    void set_y(int y);
    int distance_top() const;
    int distance_bottom() const;
    int distance_left() const;
    int distance_right() const;
    static double distance(const Pixel *p1, const Pixel *p2);
    static double distance(const Pixel &p1, const Pixel &p2);
};

#endif