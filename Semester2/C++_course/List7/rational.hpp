#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <istream>
#include <ostream>
#include <stdexcept>

using namespace std;

namespace calculations {

class RationalException : public logic_error {
public:
    RationalException(const string &msg) : logic_error(msg) {};
};

class DivisionByZero : public RationalException {
public:
    DivisionByZero() : RationalException("Division by zero!") {};
};

class OutOfRange : public RationalException {
public:
    OutOfRange() : RationalException("Result out of range - integer type overflow!") {};
};

class DenomGreaterThanZero : public RationalException {
public:
    DenomGreaterThanZero() : RationalException("Denominator must be greater than zero!") {};
};

class Rational {
private:
    int num, denom;
    void simplify();
public:
    Rational(int num, int denom);
    Rational(int num);
    Rational();
    Rational(const Rational &other);
    Rational &operator=(const Rational &other);

    int get_num() const { return num; }
    int get_denom() const { return denom; }
    void set_num(int n);
    void set_denom(int d);

    Rational &operator+=(const Rational &other);
    Rational &operator-=(const Rational &other);
    Rational &operator*=(const Rational &other);
    Rational &operator/=(const Rational &other);

    friend Rational operator-(const Rational &r);
    friend Rational operator!(const Rational &r);
    friend Rational operator+(const Rational &r1, const Rational &r2);
    friend Rational operator-(const Rational &r1, const Rational &r2);
    friend Rational operator*(const Rational &r1, const Rational &r2);
    friend Rational operator/(const Rational &r1, const Rational &r2);

    explicit operator int () const;
    operator double () const;

    friend istream& operator>>(istream &in, Rational &r);
    friend ostream& operator<<(ostream &out, const Rational &r);
};

}

#endif