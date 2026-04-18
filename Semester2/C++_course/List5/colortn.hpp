#ifndef COLORTN_HPP
#define COLORTN_HPP

#include "namedcolor.hpp"
#include "transcolor.hpp"

class ColorTn : public NamedColor, public TransColor {
public:
    ColorTn();
    ColorTn(const std::string &name, unsigned short alpha, unsigned short red,
        unsigned short green, unsigned short blue);
};

#endif