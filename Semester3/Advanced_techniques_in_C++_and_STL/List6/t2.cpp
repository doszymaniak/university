#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class Point {
public:
    string name;
    double x, y;
    short r, g, b;
    Point(string name, double x, double y, short r, short g, short b) : name(name), x(x), y(y), r(r), g(g), b(b) {};
};

void print_points(list<Point> &points)
{
    int i = 1;
    for (auto &point : points)
    {
        cout << "POINT " << i << "\n";
        cout << "name: " << point.name << '\n';
        cout << "x: " << point.x << '\n';
        cout << "y: " << point.y << '\n';
        cout << "r: " << point.r << '\n';
        cout << "g: " << point.g << '\n';
        cout << "b: " << point.b << '\n';
        cout << "\n";
        i++;
    }
}

void remove_longest(list<Point> &points)
{
    cout << "---- REMOVE POINTS WITH NAME LONGER THAN 5 CHARS ----\n";
    points.remove_if([](const Point &p) {
        return p.name.length() > 5;
    });
    print_points(points);
}

void count_quadrants(list<Point> &points)
{
    cout << "---- COUNT QUADRANTS ----\n";
    int I = 0, II = 0, III = 0, IV = 0;
    for_each(points.begin(), points.end(), [&I, &II, &III, &IV](const Point &p){
        if (p.x > 0 && p.y > 0)
            I++;
        else if (p.x < 0 && p.y > 0)
            II++;
        else if (p.x < 0 && p.y < 0)
            III++;
        else if (p.x > 0 && p.y < 0)
            IV++;
    });
    cout << "I quadrant: " << I << '\n';
    cout << "II quadrant: " << II << '\n';
    cout << "III quadrant: " << III << '\n';
    cout << "IV quadrant: " << IV << "\n\n";
}

void sort_by_brightness(list<Point> &points)
{
    cout << "---- SORTING BY BRIGHTNESS ----\n";
    points.sort([](const Point &p1, const Point &p2){
        double brightness1 = 0.3 * p1.r + 0.59 * p1.g + 0.11 * p1.b;
        double brightness2 = 0.3 * p2.r + 0.59 * p2.g + 0.11 * p2.b;
        return brightness1 < brightness2;
    });
    print_points(points);
}

void move_dark_points(list<Point> &points)
{
    cout << "---- DARK POINTS ----\n";
    list<Point> dark_points;
    for (auto it = points.begin(); it != points.end(); )
    {
        double brightness = 0.3 * it->r + 0.59 * it->g + 0.11 * it->b;
        if (brightness < 64)
        {
            dark_points.push_back(*it);
            it = points.erase(it);
        }
        else
            it++;
    }
    print_points(dark_points);
}

int main()
{
    list<Point> points = {
        {"Red", 1, 2, 255, 0, 0},
        {"Green", 3, 4, 0, 255, 0},
        {"Blue", 5, 6, 0, 0, 255},
        {"Yellow", 7, 8, 255, 255, 0},
        {"Purple", 9, 10, 128, 0, 128},
        {"Orange", 11, 12, 255, 165, 0},
        {"Pink", 13, 14, 255, 192, 203},
        {"Cyan", 15, 16, 0, 255, 255},
        {"Brown", 17, 18, 139, 69, 19},
        {"White", 19, 20, 255, 255, 255},
        {"Black", 21, 22, 0, 0, 0},
        {"Gray", 23, 24, 128, 128, 128},
        {"Gold", 25, 26, 255, 215, 0},
        {"Silver", 27, 28, 192, 192, 192},
        {"Navy", 29, 30, 0, 0, 128},
        {"Lime", 31, 32, 50, 205, 50},
        {"Coral", 33, 34, 255, 127, 80},
        {"Indigo", 35, 36, 75, 0, 130},
        {"Violet", 37, 38, 238, 130, 238},
        {"Beige", 39, 40, 245, 245, 220},
        {"Teal", 41, 42, 0, 128, 128},
        {"Olive", 43, 44, 128, 128, 0},
        {"Maroon", 45, 46, 128, 0, 0}
    };

    remove_longest(points);

    count_quadrants(points);

    sort_by_brightness(points);

    move_dark_points(points);
}