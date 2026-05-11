#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <ostream>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct point {
    int x;
    int y;
};

ostream &operator<<(ostream &out, const point &p)
{
    out << "{" << p.x << ", " << p.y << "}";
    return out;
}

template<typename T>
void arrprint(const T arr[], int siz, ostream &out = cout)
{
    for (int i = 0; i < siz; i++) out << arr[i] << " ";
    out << "\n";
}

template<typename T>
void arrcopy(const T from[], int siz, T to[])
{
    for (int i = 0; i < siz; i++) to[i] = from[i];
}

template<typename T>
void arrpermut(T arr[], int siz)
{
    for (int i = siz - 1; i > 0; i--)
    {
        int random_idx = rand() % (i + 1);
        swap(arr[i], arr[random_idx]);
    }
}

template<typename T>
class Less {
    public:
        bool operator() (const T &a, const T &b)
        {
            return a < b;
        }
};

template<typename T>
class Greater {
    public:
        bool operator() (const T &a, const T &b)
        {
            return a > b;
        }
};

template<>
class Less<const char*> {
    public:
        bool operator() (const char *a, const char *b)
        {
            return strcmp(a, b) < 0;
        }
};

template<>
class Greater<const char *> {
    public:
        bool operator() (const char *a, const char *b)
        {
            return strcmp(a, b) > 0;
        }
};

template<>
class Less<point> {
    public:
        bool operator() (const point &a, const point &b)
        {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        }
};

template<>
class Greater<point> {
    public:
        bool operator() (const point &a, const point &b)
        {
            if (a.x != b.x) return a.x > b.x;
            return a.y > b.y;
        }
};

template<typename T, typename Comp = Less<T>>
void bubble_sort(T arr[], int siz, Comp comp = Comp())
{
    for (int i = 0; i < siz - 1; i++)
    {
        for (int j = 0; j < siz - i - 1; j++)
        {
            if (comp(arr[j + 1], arr[j])) swap(arr[j], arr[j + 1]);
        }
    }
}

template<typename T, typename Comp>
void merge(T arr[], int left, int mid, int right, Comp comp)
{
    int i = left;
    int j = mid + 1;
    vector<T> temp(right - left + 1);
    int idx = 0;
    while (i <= mid && j <= right)
    {
        if (comp(arr[j], arr[i])) temp[idx++] = arr[j++];
        else temp[idx++] = arr[i++];
    }
    while (i <= mid) temp[idx++] = arr[i++];
    while (j <= right) temp[idx++] = arr[j++];
    
    idx = 0;
    for (int k = left; k <= right; k++) arr[k] = temp[idx++];
}

template<typename T, typename Comp>
void merge_rec(T arr[], int left, int right, Comp comp)
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_rec(arr, left, mid, comp);
    merge_rec(arr, mid + 1, right, comp);
    merge(arr, left, mid, right, comp);
}

template<typename T, typename Comp = Less<T>>
void merge_sort(T arr[], int siz, Comp comp = Comp())
{
    merge_rec(arr, 0, siz - 1, comp);
}

#endif