#include "manipulators.hpp"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool cmp(const pair<int, string> &p1, const pair<int, string> &p2)
{
    return p1.second < p2.second;
}

void file_test()
{
    ifstream in("test.txt");
    vector<pair<int, string>> lines;
    int cnt = 1;
    string line = "";
    while (getline(in, line))
    {
        lines.push_back({cnt, line});
        cnt++;
    }
    sort(lines.begin(), lines.end(), cmp);
    for (auto &line : lines) cout << index(line.first, 3) << " " << line.second << '\n';
}

int main()
{
    cout << "-- FILE TEST --\n";
    file_test();
    
    string s;
    cout << "\n-- IGNORE TEST --\n";
    cout << "Enter string: ";
    cin >> mignore(5);
    cin >> s;
    cout << "After ignore(5): " << s << '\n';

    cout << "\n-- INDEX TEST --\n";
    cout << index(1, 2) << " " << "With index 1\n";

    s = "";
    cout << "\n-- CLEARLINE TEST --\n";
    cout << "Enter string (line 1): ";
    cin >> clearline >> s;
    cout << "\nEnter string (line 2): ";
    cin >> s;
    cout << "After clearline: " << s << '\n';
    return 0;
}