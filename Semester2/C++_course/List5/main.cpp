#include <iostream>
#include "color.hpp"
#include "colorpixel.hpp"
#include "colortn.hpp"
#include "namedcolor.hpp"
#include "pixel.hpp"
#include "transcolor.hpp"

using namespace std;

int main()
{
    cout << "-- COLOR TEST --\n";
    Color c1(45, 67, 89);
    Color c2(48, 34, 0);
    cout << "Color 1: " << c1.get_red() << " " << c1.get_green() << " " << c1.get_blue() << '\n';
    cout << "Color 2: " << c2.get_red() << " " << c2.get_green() << " " << c2.get_blue() << '\n';

    c1.darken(15);
    cout << "Color 1 darkened by 15: ";
    cout << c1.get_red() << " " << c1.get_green() << " " << c1.get_blue() << '\n';

    c2.lighten(50);
    cout << "Color 2 lightened by 50: ";
    cout << c2.get_red() << " " << c2.get_green() << " " << c2.get_blue() << '\n';

    Color c3 = Color::blend(c1, c2);
    cout << "Color 1 and Color 2 blended: ";
    cout << c3.get_red() << " " << c3.get_green() << " " << c3.get_blue() << '\n';


    cout << "\n\n -- TRANSCOLOR TEST --\n";
    TransColor t = TransColor(17, 4, 5, 6);
    cout << "Transparent color: \n";
    cout << "Alpha: " << t.get_alpha() << '\n';
    cout << "Red: " << t.get_red() << '\n';
    cout << "Green: " << t.get_green() << '\n';
    cout << "Blue: " << t.get_blue() << '\n';


    cout << "\n\n -- NAMEDCOLOR TEST --\n";
    NamedColor n = NamedColor("somename", 4, 5, 6);
    cout << "Named color: \n";
    cout << "Name: " << n.get_name() << '\n';
    cout << "Red: " << n.get_red() << '\n';
    cout << "Green: " << n.get_green() << '\n';
    cout << "Blue: " << n.get_blue() << '\n';


    cout << "\n\n -- COLORTN TEST --\n";
    ColorTn tn = ColorTn("somename", 28, 4, 5, 6);
    cout << "Named transparent color: \n";
    cout << "Name: " << tn.get_name() << '\n';
    cout << "Alpha: " << tn.get_alpha() << '\n';
    cout << "Red: " << tn.get_red() << '\n';
    cout << "Green: " << tn.get_green() << '\n';
    cout << "Blue: " << tn.get_blue() << '\n';



    cout << "\n\n-- PIXEL TEST --\n";
    Pixel p1(155, 599);
    Pixel p2(350, 200);
    cout << "Pixel 1: " << p1.get_x() << " " << p1.get_y() << '\n';
    cout << "Pixel 2: " << p2.get_x() << " " << p2.get_y() << '\n';

    cout << "\nPixel 1 distances:\n";
    cout << "Distance from top: " << p1.distance_top() << '\n';
    cout << "Distance from bottom: " << p1.distance_bottom() << '\n';
    cout << "Distance from left: " << p1.distance_left() << '\n';
    cout << "Distance from right: " << p1.distance_right() << '\n';

    cout << "\nDistance between Pixel 1 and Pixel 2: " << Pixel::distance(p1, p2) << '\n';



    cout << "\n\n-- COLORPIXEL TEST --\n";
    cout << "Colored pixel: \n";
    ColorPixel pc(23, 300, 45, 67, 89);
    cout << "x: " << pc.get_x() << '\n';
    cout << "y: " << pc.get_y() << '\n';
    cout << "Red: " << pc.get_red() << '\n';
    cout << "Green: " << pc.get_green() << '\n';
    cout << "Blue: " << pc.get_blue() << '\n';

    pc.move(5, 5);
    cout << "\nPixel moved by vector [5; 5]: " << pc.get_x() << " " << pc.get_y() << '\n';

    cout << "\nPixel move out of bounds: ";
    try
    {
        pc.move(800, 600);
    }
    catch (const exception& e)
    {
        cerr << e.what() << "\n";
    }
    return 0;
}