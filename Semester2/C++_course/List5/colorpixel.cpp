#include "color.hpp"
#include "colorpixel.hpp"

using namespace std;

typedef unsigned short us;

ColorPixel::ColorPixel(int x, int y, us r, us g, us b) : Pixel(x, y), Color(r, g, b) {}

void ColorPixel::move(int dx, int dy)
{
    int new_x = get_x() + dx;
    int new_y = get_y() + dy;
    set_x(new_x);
    set_y(new_y);
}

us ColorPixel::get_red() const { return Color::get_red(); }

us ColorPixel::get_green() const { return Color::get_green(); }

us ColorPixel::get_blue() const { return Color::get_blue(); }