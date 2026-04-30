#include "rational.hpp"
#include <numeric>
#include <limits.h>
#include <cmath>
#include <map>

using namespace std;

namespace calculations {

Rational::Rational() : num(0), denom(1) {}

Rational::Rational(int n, int d) : num(n), denom(d) 
{
    if (denom <= 0) throw DenomGreaterThanZero();
    this->simplify();
}

Rational::Rational(int num) : Rational(num, 1) {}

Rational::Rational(const Rational &other)
{
    num = other.num;
    denom = other.denom;
}

Rational &Rational::operator=(const Rational &other)
{
    num = other.num;
    denom = other.denom;
    return *this;
}

void Rational::set_num(int n)
{
    this->num = n;
}

void Rational::set_denom(int d)
{
    if (d <= 0) throw DenomGreaterThanZero();
    this->denom = d;
}

Rational operator-(const Rational &r)
{
    Rational new_r = r;
    int r_num = new_r.get_num();
    new_r.set_num(-r_num);
    return new_r;
}

Rational operator!(const Rational &r)
{
    Rational new_r = r;
    int new_num = new_r.get_denom();
    int new_denom = new_r.get_num();
    if (new_denom == 0) throw DivisionByZero();
    if (new_denom < 0) 
    {
        new_denom = -new_denom;
        new_num = -new_num;
    }
    new_r.set_num(new_num);
    new_r.set_denom(new_denom);
    return new_r;
}

void Rational::simplify()
{
    int g = gcd(num, denom);
    num /= g;
    denom /= g;
}

Rational &Rational::operator+=(const Rational &other)
{
    long long other_denom = other.get_denom();
    long long other_num = other.get_num();
    long long res_denom = lcm(denom, other_denom);
    long long res_num = (res_denom / denom) * num + (res_denom / other_denom) * other_num;
    if (res_denom > INT_MAX || res_denom < INT_MIN || res_num > INT_MAX || res_num < INT_MIN) throw OutOfRange();
    this->set_num(res_num);
    this->set_denom(res_denom);
    this->simplify();
    return *this;
}

Rational &Rational::operator-=(const Rational &other)
{
    long long other_denom = other.get_denom();
    long long other_num = other.get_num();
    long long res_denom = lcm(denom, other_denom);
    long long res_num = (res_denom / denom) * num - (res_denom / other_denom) * other_num;
    if (res_denom > INT_MAX || res_denom < INT_MIN || res_num > INT_MAX || res_num < INT_MIN) throw OutOfRange();
    this->set_num(res_num);
    this->set_denom(res_denom);
    this->simplify();
    return *this;
}

Rational &Rational::operator*=(const Rational &other)
{
    long long other_denom = other.get_denom();
    long long other_num = other.get_num();
    long long res_denom = other_denom * denom;
    long long res_num = other_num * num;
    if (res_denom > INT_MAX || res_denom < INT_MIN || res_num > INT_MAX || res_num < INT_MIN) throw OutOfRange();
    this->set_num(res_num);
    this->set_denom(res_denom);
    this->simplify();
    return *this;
}

Rational &Rational::operator/=(const Rational &other)
{
    if (other.get_num() == 0) throw DivisionByZero();
    const Rational reciprocal = !(other);
    return *this *= reciprocal;
}

Rational operator+(const Rational &r1, const Rational &r2)
{
    Rational res(r1);
    res += r2;
    return res;
}

Rational operator-(const Rational &r1, const Rational &r2)
{
    Rational res(r1);
    res -= r2;
    return res;
}

Rational operator*(const Rational &r1, const Rational &r2)
{
    Rational res(r1);
    res *= r2;
    return res;
}

Rational operator/(const Rational &r1, const Rational &r2)
{
    Rational res(r1);
    res /= r2;
    return res;
}

Rational::operator double () const
{
    return static_cast<double>(num) / denom;
}

Rational::operator int () const 
{
    return static_cast<int>(round((double)*this));
}

istream &operator>>(istream &in, Rational &r)
{
    int num, denom;
    char c;
    in >> num >> c >> denom;
    if (c != '/') throw invalid_argument("Slash is expected!");
    r.set_num(num);
    r.set_denom(denom);
    r.simplify();
    return in;
}

ostream &operator<<(ostream &out, const Rational &r)
{
    int num = abs(r.get_num());
    int denom = r.get_denom();
    int integral = num / denom;
    int remainder = num % denom;
    string fractional;
    map<int, int> m;
    int position = 0;
    bool is_negative = r.get_num() < 0 ? 1 : 0;
    while (1)
    {
        remainder *= 10;
        int digit = remainder / denom;
        auto it = m.find(remainder);
        if (it != m.end())
        {
            int pos = m[remainder];
            fractional.insert(pos, "(");
            fractional += ')';
            break;
        }
        fractional += to_string(digit);
        int modulo = remainder % denom;
        if (modulo == 0) break;
        m[remainder] = position;
        position++;
        remainder = modulo;
    }
    string final = to_string(integral) + "." + fractional;
    if (is_negative) out << '-' << final;
    else out << final;
    return out;
}

}