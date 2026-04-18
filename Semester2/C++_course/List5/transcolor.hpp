#ifndef TRANSCOLOR_HPP
#define TRANSCOLOR_HPP

#include "color.hpp"

class TransColor : virtual public Color {
private:
    unsigned short alpha;
public:
    TransColor();
    TransColor(unsigned short alpha, unsigned short red, unsigned short green, unsigned short blue);
    unsigned short get_alpha() const;
    void set_alpha(unsigned short alpha);
};

#endif