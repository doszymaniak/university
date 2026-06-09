#include "manipulators.hpp"
#include <string>
#include <iomanip>

using namespace std;

istream &clearline(istream &in)
{
    char c;
    while (in.get(c))
    {
        if (c == '\n') break;
    }
    return in;
}

istream &operator>>(istream &in, const Ignore &ig)
{
    char c;
    for (int cnt = 0; cnt < ig.x && in.get(c); cnt++)
    {
        if (c == '\n') break;
    }
    return in;
}

ostream &comma(ostream &out)
{
    return out << ", ";
}

ostream &colon(ostream &out)
{
    return out << ": ";
}

ostream &operator<<(ostream &out, const Index &idx)
{
    out << "[" << setw(idx.w) << idx.x << "]";
    return out;
}

Index index(int x, int w)
{
    return Index(x, w);
}

Ignore mignore(int x)
{
    return Ignore(x);
}