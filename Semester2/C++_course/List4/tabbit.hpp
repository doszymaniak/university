#ifndef TABBIT_HPP
#define TABBIT_HPP

#include <cstdint>
#include <istream>
#include <ostream>

using namespace std;

class Tabbit {
    typedef uint64_t cell;
    static const int unit = 64; // bits per one cell
    friend istream  &operator>>(istream &in, Tabbit &t);
    friend ostream &operator<<(ostream &out, const Tabbit &t);

    class Ref {
    private:
        Tabbit &tab;
        int idx;
    public:
        Ref(Tabbit &t, int i);
        operator bool() const;
        Ref &operator=(bool val);
        Ref &operator=(const Ref &other);
    };

protected:
    int len; // number of bits
    cell *tab; // array of bits
public:
    // array of bits [0...s]
    explicit Tabbit(int s);
    // array of bits initialized by 64-bit variable
    explicit Tabbit(cell tb);
    ~Tabbit();
    Tabbit(const Tabbit &other);
    Tabbit(Tabbit &&other);
    Tabbit &operator=(const Tabbit &other);
    Tabbit &operator=(Tabbit &&other);
private:
    bool read(int i) const;
    void write(int i, bool b);
public:
    bool operator[](int i) const;
    Ref operator[](int i);
    inline int bits_per_tabbit() const;
    Tabbit operator|(const Tabbit &other) const;
    Tabbit &operator|=(const Tabbit &other);
    Tabbit operator&(const Tabbit &other) const;
    Tabbit &operator&=(const Tabbit &other);
    Tabbit operator^(const Tabbit &other) const;
    Tabbit &operator^=(const Tabbit &other);
    Tabbit operator!() const;
    void print_tabbit(const string &label) const;
};

#endif