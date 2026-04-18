#ifndef NAMEDCOLOR_HPP
#define NAMEDCOLOR_HPP

#include "color.hpp"
#include <string>

class NamedColor : virtual public Color {
private:
    std::string name;
public:
    NamedColor();
    NamedColor(unsigned short red, unsigned short green, unsigned short blue);
    NamedColor(const std::string &name, unsigned short red, unsigned short green, unsigned short blue);
    const std::string &get_name() const;
    void set_name(const std::string &name);
    void check_name(const std::string &name);
};

#endif