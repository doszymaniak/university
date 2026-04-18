#include "color.hpp"
#include "namedcolor.hpp"
#include <stdexcept>
#include <string>

using namespace std;

typedef unsigned short us;

void NamedColor::check_name(const string &n)
{
    for (auto c : n)
    {
        if (!isalpha(c)) throw invalid_argument("Name must contain letters only!");
    }
}

NamedColor::NamedColor() : Color(), name("") {}

NamedColor::NamedColor(us r, us g, us b) : Color(r, g, b), name("") {}

NamedColor::NamedColor(const string &n, us r, us g, us b) : Color(r, g, b), name(n) 
{
    check_name(n);
}

const string &NamedColor::get_name() const { return name; }

void NamedColor::set_name(const string &n)
{
    check_name(n);
    name = n;
}