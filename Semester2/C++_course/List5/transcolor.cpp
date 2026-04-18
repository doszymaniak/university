#include "color.hpp"
#include "transcolor.hpp"
#include <stdexcept>

using namespace std;

typedef unsigned short us;

TransColor::TransColor() : Color(), alpha(0) {}

TransColor::TransColor(us a, us r, us g, us b) : Color(r, g, b), alpha(a) 
{
    if (alpha > 255) throw out_of_range("Alpha out of range!");
}

us TransColor::get_alpha() const { return alpha; }

void TransColor::set_alpha(us a)
{
    if (a > 255) throw out_of_range("Alpha out of range!");
    alpha = a;
}