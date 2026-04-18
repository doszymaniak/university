#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
private:
    unsigned short red;
    unsigned short green;
    unsigned short blue;
public:
    Color();
    Color(unsigned short red, unsigned short green, unsigned short blue);
    unsigned short get_red() const;
    unsigned short get_green() const;
    unsigned short get_blue() const;
    void set_red(unsigned short val);
    void set_green(unsigned short val);
    void set_blue(unsigned short val);
    void lighten(unsigned short val);
    void darken(unsigned short val);
    static Color blend(const Color &first, const Color &second);
    void check_color_val(unsigned short val);
};

#endif