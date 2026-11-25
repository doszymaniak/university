#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Please enter a file name as an argument!";
        return 1;
    }
    ifstream file(argv[1]);
    if (!file)
    {
        cout << "Cannot open the file!";
        return 1;
    }

    istream_iterator<char> file_it(file);
    istream_iterator<char> eos;
    map<char, int> freq;
    int total_letters = 0;
    for_each(file_it, eos, [&freq, &total_letters](const char &c){
        if (isalpha(c))
        {
            freq[tolower(c)]++;
            total_letters++;
        }
    });

    for (auto l : freq)
    {
        double frequency = static_cast<double>(l.second) / total_letters;
        cout << l.first << ": " << l.second << " | " << fixed << setprecision(4) << frequency * 100 << "%\n";
    }

    cout << "Total letters: " << total_letters << '\n';
    return 0;
}