#include "pixel.hpp"
#include <stdexcept>
#include <cmath>

using namespace std;

void Pixel::check_coordinates(int x, int y)
{
    if (x < 0 || y < 0 || x >= disp_x || y >= disp_y) throw out_of_range("Coordinates out of range!");
}

Pixel::Pixel(int x, int y) : x(x), y(y)
{
    check_coordinates(x, y);
}

int Pixel::get_x() const { return x; }

int Pixel::get_y() const { return y; }

void Pixel::set_x(int val)
{
    check_coordinates(val, y);
    x = val;
}

void Pixel::set_y(int val)
{
    check_coordinates(x, val);
    y = val;
}

int Pixel::distance_top() const { return y; }

int Pixel::distance_bottom() const { return disp_y - y; }

int Pixel::distance_left() const { return x; }

int Pixel::distance_right() const { return disp_x - x; }

double Pixel::distance(const Pixel &p1, const Pixel &p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

double Pixel::distance(const Pixel *p1, const Pixel *p2)
{
    if (p1 == nullptr || p2 == nullptr) throw invalid_argument("Empty pixels!");
    return distance(*p1, *p2);
}