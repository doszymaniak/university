#ifndef COLORPIXEL_HPP
#define COLORPIXEL_HPP

#include "pixel.hpp"
#include "color.hpp"

class ColorPixel final : public Pixel, private Color {
public:
    ColorPixel(int x, int y, unsigned short red, unsigned short green, unsigned short blue);
    void move(int dx, int dy);
    unsigned short get_red() const;
    unsigned short get_green() const;
    unsigned short get_blue() const;
};

#endif