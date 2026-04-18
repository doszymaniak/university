#include "colortn.hpp"
#include "namedcolor.hpp"
#include "transcolor.hpp"
#include "color.hpp"

using namespace std;

typedef unsigned short us;

ColorTn::ColorTn() : NamedColor(), TransColor() {}

ColorTn::ColorTn(const string &n, us a, us r, us g, us b) :
    Color(r, g, b), NamedColor(n, r, g, b), TransColor(a, r, g, b) {}