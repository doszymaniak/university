#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

template <typename T>
class Range {
private:
    T a, b;

public:
    Range(T a, T b) : a(a), b(b) {}

    void operator () (const T &x) const
    {
        if (x > a && x < b)
            cout << x << " ";
    }
};

template <typename T>
class EveryK {
private:
    int k, p, pos;

public:
    EveryK(int k, int p) : k(k), p(p), pos(1) {}

    void operator () (const T &x)
    {
        if (k > 0 && pos >= p && (pos - p) % k == 0)
            cout << x << " ";
        pos++;
    }
};

template<typename T>
class MinMax {
private:
    int i;
    T curr_min, curr_max;

public:
    MinMax() : i(0) {}

    void operator () (const T &x)
    {
        if (i == 0)
        {
            curr_min = x;
            curr_max = x;
        }
        else
        {
            if (x < curr_min)
                curr_min = x;
            if (x > curr_max)
                curr_max = x;
        }
        i++;
    }

    pair<T, T> getResult() const
    {   
        if (i == 0)
            throw runtime_error("Container is empty!");
        return {curr_min, curr_max};
    }
};

int main()
{
    set<string> s = {"jakies", "przypadkowe", "slowa", "ala", "ma", "kota", "a", "b", "c", "d"};
    vector<double> v = {4.5, 3.45, 7.4, 9.5, 6435.4, 45.7, 454.7, 31.8, 45.9, 56.65, 88.5, 56.9};
    list<int> l = {3, 54, 1, 5, 6, 7, 9, 4, 1, 5, 65, 78, 43, 35, 87, 32, 5};

    cout << "---- VALUES WITHIN RANGE (a, b) ----\n";
    cout << "vector: ";
    for_each(v.begin(), v.end(), Range<double>(3.0, 90.0));
    cout << "\n";

    cout << "list: ";
    for_each(l.begin(), l.end(), Range<int>(5, 80));
    cout << "\n";

    cout << "set: ";
    for_each(s.begin(), s.end(), Range<string>("a", "z"));
    cout << "\n";


    cout << "\n---- EVERY K-TH VALUE ----\n";
    cout << "vector: ";
    for_each(v.begin(), v.end(), EveryK<double>(2, 2));
    cout << "\n";

    cout << "list: ";
    for_each(l.begin(), l.end(), EveryK<int>(3, 1));
    cout << "\n";

    cout << "set: ";
    for_each(s.begin(), s.end(), EveryK<string>(2, 1));
    cout << "\n";


    cout << "\n---- MINIMUM AND MAXIMUM ----\n";
    cout << "vector: ";
    MinMax<double> mm1;
    for (double x : v) mm1(x);
    auto result1 = mm1.getResult();
    cout << "min - " << result1.first << ", ";
    cout << "max - " << result1.second << '\n';

    cout << "list: ";
    MinMax<int> mm2;
    for (int x : l) mm2(x);
    auto result2 = mm2.getResult();
    cout << "min - " << result2.first << ", ";
    cout << "max - " << result2.second << '\n';

    cout << "set: ";
    MinMax<string> mm3;
    for (const string &x : s) mm3(x);
    auto result3 = mm3.getResult();
    cout << "min - " << result3.first << ", ";
    cout << "max - " << result3.second << '\n';
    return 0;
}
