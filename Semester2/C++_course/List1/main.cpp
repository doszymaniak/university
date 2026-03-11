#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

const vector<pair<int, string>> roman =
{
    {1000, "M"},
    {900, "CM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},
    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"}
};

string to_roman(int x)
{
    string res = "";
    int idx = 0;
    while (x > 0)
    {
        int how_many = x / roman[idx].first;
        while (how_many)
        {
            res += roman[idx].second;
            how_many--;
        }
        x %= roman[idx].first;
        idx++;
    }
    return res;
}

int main(int argc, const char *argv[])
{
    if (argc <= 1)
    {
        clog << "No numbers to convert!\n";
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        string argv_str = argv[i];
        int num = 0;
        try
        {
            num = stoi(argv_str);
        }
        catch (const invalid_argument &e)
        {
            clog << argv_str << " is not an integer!\n";
            continue;
        }
        if (num < 1 || num > 3999)
        {
            try 
            {
                throw invalid_argument("Out of range");
            }
            catch (const invalid_argument &e)
            {
                clog << argv_str << " is out of range (1 - 3999)!\n";
                continue;
            }
        }
        cout << to_roman(num) << '\n';
    }
    return 0;
}