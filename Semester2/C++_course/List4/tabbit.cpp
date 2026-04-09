#include "tabbit.hpp"
#include <stdexcept>
#include <iostream>

istream &operator>>(istream &in, Tabbit &tab)
{
    char c;
    for (int i = 0; i < tab.bits_per_tabbit(); i++)
    {
        in >> c;
        if (c == '1') tab.write(i, true);
        else if (c == '0') tab.write(i, false);
        else throw invalid_argument("Invalid input!");
    }
    return in;
}

ostream &operator<<(ostream &out, const Tabbit &tab)
{
    for (int i = 0; i < tab.bits_per_tabbit(); i++)
    {
        bool bit = tab.read(i);
        if (bit) out << '1';
        else out << '0';
    }
    return out;
}

Tabbit::Tabbit(int s)
{
    len = s;
    int how_many_cells = (len + unit - 1) / unit;
    tab = new cell[how_many_cells];
    for (int i = 0; i < how_many_cells; i++) tab[i] = 0;
}

Tabbit::Tabbit(cell tb)
{
    tab = new cell[1];
    tab[0] = tb;
    len = unit;
}

Tabbit::~Tabbit()
{
    delete[] tab;
    len = 0;
}

Tabbit::Tabbit(const Tabbit &other)
{
    len = other.len;
    int num_cells = (len + unit - 1) / unit;
    tab = new cell[num_cells];
    for (int i = 0; i < num_cells; i++) tab[i] = other.tab[i];
}

Tabbit::Tabbit(Tabbit &&other)
{
    len = other.len;
    tab = other.tab;
    other.tab = nullptr;
    other.len = 0;
}

Tabbit &Tabbit::operator=(const Tabbit &other)
{
    if (this != &other)
    {
        len = other.len;
        delete[] tab;
        int num_cells = (len + unit - 1) / unit;
        tab = new cell[num_cells];
        for (int i = 0; i < num_cells; i++) tab[i] = other.tab[i];
    }
    return *this;
}

Tabbit &Tabbit::operator=(Tabbit &&other)
{
    if (this != &other)
    {
        len = other.len;
        delete[] tab;
        tab = other.tab;
        other.tab = nullptr;
        other.len = 0;
    }
    return *this;
}

bool Tabbit::read(int i) const
{
    if (i < 0 || i >= bits_per_tabbit()) throw out_of_range("Index out of range!");
    int cell_idx = i / unit;
    int bit_idx = i % unit;
    return (tab[cell_idx] >> bit_idx) & 1;
}

void Tabbit::write(int i, bool b)
{
    if (i < 0 || i >= bits_per_tabbit()) throw out_of_range("Index out of range!");
    int cell_idx = i / unit;
    int bit_idx = i % unit;
    tab[cell_idx] &= (~(1ULL << bit_idx));
    int64_t bit = (b ? 1 : 0);
    bit <<= bit_idx;
    tab[cell_idx] |= bit;
}

Tabbit::Ref::Ref(Tabbit &t, int i) : tab(t), idx(i) {};

Tabbit::Ref::operator bool() const { return tab.read(idx); }

Tabbit::Ref &Tabbit::Ref::operator=(bool val) { tab.write(idx, val); return *this; }

Tabbit::Ref &Tabbit::Ref::operator=(const Ref &other) { *this = bool(other); return *this; }

bool Tabbit::operator[](int i) const 
{
    if (i < 0 || i >= bits_per_tabbit()) throw out_of_range("Index out of range!");
    return read(i);
}

Tabbit::Ref Tabbit::operator[](int i)
{
    if (i < 0 || i >= bits_per_tabbit()) throw out_of_range("Index out of range!");
    return Ref(*this, i);
}

inline int Tabbit::bits_per_tabbit() const
{
    return len;
}

Tabbit Tabbit::operator|(const Tabbit &other) const
{
    if (other.len != len) throw invalid_argument("Lengths don't match!");
    Tabbit res(*this);
    int cells = (len + unit - 1) / unit;
    for (int i = 0; i < cells; i++) res.tab[i] |= other.tab[i];
    return res;
}

Tabbit &Tabbit::operator|=(const Tabbit &other)
{
    if (&other == this) return *this;
    if (other.len != len) throw invalid_argument("Lengths don't match!");
    int cells = (len + unit - 1) / unit;
    for (int i = 0; i < cells; i++) tab[i] |= other.tab[i];
    return *this;
}

Tabbit Tabbit::operator&(const Tabbit &other) const
{
    if (other.len != len) throw invalid_argument("Lengths don't match!");
    Tabbit res(*this);
    int cells = (len + unit - 1) / unit;
    for (int i = 0; i < cells; i++) res.tab[i] &= other.tab[i];
    return res;
}

Tabbit &Tabbit::operator&=(const Tabbit &other)
{
    if (&other == this) return *this;
    if (other.len != len) throw invalid_argument("Lengths don't match!");
    int cells = (len + unit - 1) / unit;
    for (int i = 0; i < cells; i++) tab[i] &= other.tab[i];
    return *this;
}

Tabbit Tabbit::operator^(const Tabbit &other) const
{
    if (other.len != len) throw invalid_argument("Lengths don't match!");
    Tabbit res(*this);
    int cells = (len + unit - 1) / unit;
    for (int i = 0; i < cells; i++) res.tab[i] ^= other.tab[i];
    return res;
}

Tabbit &Tabbit::operator^=(const Tabbit &other)
{
    if (&other == this) return *this;
    if (other.len != len) throw invalid_argument("Lengths don't match!");
    int cells = (len + unit - 1) / unit;
    for (int i = 0; i < cells; i++) tab[i] ^= other.tab[i];
    return *this;
}

Tabbit Tabbit::operator!() const
{
    Tabbit res(*this);
    int cells = (len + unit - 1) / unit;
    for (int i = 0; i < cells; i++) res.tab[i] = ~tab[i];
    int64_t excess_bits = cells * unit - len;
    if (excess_bits > 0) res.tab[cells - 1] &= ((1ULL << (unit - excess_bits)) - 1);
    return res;
}

void Tabbit::print_tabbit(const string &label) const
{
    cout << label << '\n' << *this << "\n\n";
}