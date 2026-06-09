#ifndef MANIPULATORS_HPP
#define MANIPULATORS_HPP

#include <istream>

using namespace std;

istream &clearline(istream &in);

class Ignore {
private:
    int x;
public:
    Ignore(int a) : x(a) {};
    friend istream &operator>>(istream &in, const Ignore& ig);
};

Ignore mignore(int x);

ostream &comma(ostream &out);
ostream &colon(ostream &out);

class Index {
private:
    int x;
    int w;
public:
    Index(int a, int b) : x(a), w(b) {};
    friend ostream &operator<<(ostream &out, const Index& idx);
};

Index index(int x, int w);

#endif