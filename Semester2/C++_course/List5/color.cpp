#include "color.hpp"
#include <stdexcept>

using namespace std;

typedef unsigned short us;

void Color::check_color_val(us val)
{
    if (val > 255) throw out_of_range("Value out of range!");
}

Color::Color() : red(0), green(0), blue(0) {}

Color::Color(us r, us g, us b) : red(r), green(g), blue(b)
{
    check_color_val(r);
    check_color_val(g);
    check_color_val(b);
}

void Color::set_red(us v)
{
    check_color_val(v);
    red = v;
}

void Color::set_blue(us v)
{
    check_color_val(v);
    blue = v;
}

void Color::set_green(us v)
{
    check_color_val(v);
    green = v;
}

us Color::get_red() const { return red; }

us Color::get_green() const { return green; }

us Color::get_blue() const { return blue; }

void Color::darken(us val)
{
    red = val > red ? 0 : red - val;
    green = val > green ? 0 : green - val;
    blue = val > blue ? 0 : blue - val;
}

void Color::lighten(us val)
{
    red = min(255, red + val);
    green = min(255, green + val);
    blue = min(255, blue + val);
}

Color Color::blend(const Color &first, const Color &second)
{
    us r = (first.get_red() + second.get_red()) / 2;
    us g = (first.get_green() + second.get_green()) / 2;
    us b = (first.get_blue() + second.get_blue()) / 2;
    return Color(r, g, b);
}