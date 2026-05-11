#include "templates.hpp"
#include <stdio.h>

using namespace std;

int main()
{
    // INTEGER
    int int_arr[] = {1, 2, 3, 4, 5, 6};
    cout << "integer array: ";
    arrprint(int_arr, 6);

    cout << "shuffled: ";
    int i2[6] = {};
    arrcopy(int_arr, 6, i2);
    arrpermut(i2, 6);
    arrprint(i2, 6);

    int i3[6] = {};
    arrcopy(i2, 6, i3);
    cout << "bubble sort (<): ";
    bubble_sort(i3, 6);
    arrprint(i3, 6);

    cout << "bubble sort (>): ";
    bubble_sort(i3, 6, Greater<int>());
    arrprint(i3, 6);

    cout << "merge sort (<): ";
    merge_sort(i2, 6);
    arrprint(i2, 6);

    cout << "merge sort (>): ";
    merge_sort(i2, 6, Greater<int>());
    arrprint(i2, 6);


    // STRING
    string str_arr[] = {"this", "is", "a", "sample", "array"};
    cout << "\nstring array: ";
    arrprint(str_arr, 5);

    cout << "shuffled: ";
    string s2[5] = {};
    arrcopy(str_arr, 5, s2);
    arrpermut(s2, 5);
    arrprint(s2, 5);

    cout << "bubble sort (<): ";
    string s3[5] = {};
    arrcopy(s2, 5, s3);
    bubble_sort(s3, 5);
    arrprint(s3, 5);

    cout << "bubble sort (>): ";
    bubble_sort(s3, 5, Greater<string>());
    arrprint(s3, 5);

    cout << "merge sort (<): ";
    merge_sort(s2, 5);
    arrprint(s2, 5);

    cout << "merge sort (>): ";
    merge_sort(s2, 5, Greater<string>());
    arrprint(s2, 5);


    // CONST CHAR *
    const char *char_arr[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    cout << "\nconst char arr: ";
    arrprint(char_arr, 8);

    cout << "shuffled: ";
    const char *c2[8] = {};
    arrcopy(char_arr, 8, c2);
    arrpermut(c2, 8);
    arrprint(c2, 8);

    cout << "bubble sort (<): ";
    const char *c3[8] = {};
    arrcopy(c2, 8, c3);
    bubble_sort(c3, 8);
    arrprint(c3, 8);

    cout << "bubble sort (>): ";
    bubble_sort(c3, 8, Greater<const char *>());;
    arrprint(c3, 8);

    cout << "merge sort (<): ";
    merge_sort(c2, 8);
    arrprint(c2, 8);

    cout << "merge sort (>): ";
    merge_sort(c2, 8, Greater<const char *>());
    arrprint(c2, 8);


    // POINT
    point point_arr[] = {{1, 1}, {1, 2}, {2, 3}, {4, 5}, {7, 8}};
    cout << "\npoint arr: ";
    arrprint(point_arr, 5);

    cout << "shuffled: ";
    point p2[5] = {};
    arrcopy(point_arr, 5, p2);
    arrpermut(p2, 5);
    arrprint(p2, 5);

    cout << "bubble sort (<): ";
    point p3[5] = {};
    arrcopy(p2, 5, p3);
    bubble_sort(p3, 5);
    arrprint(p3, 5);

    cout << "bubble sort (>): ";
    bubble_sort(p3, 5, Greater<point>());
    arrprint(p3, 5);

    cout << "merge sort (<): ";
    merge_sort(p2, 5);
    arrprint(p2, 5);

    cout << "merge sort (>): ";
    merge_sort(p2, 5, Greater<point>());
    arrprint(p2, 5);
    return 0;
}