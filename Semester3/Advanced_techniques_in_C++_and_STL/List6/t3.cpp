#include <vector>
#include <iostream>
#include <map>

using namespace std;

vector<pair<int, int>> most_frequent(vector<int> &v)
{
    map<int, int> freq;
    for (auto n : v)
        freq[n]++;
    int max_freq = 0;
    for (auto &[first, second] : freq)
    {
        if (second > max_freq)
            max_freq++;
    }
    vector<pair<int, int>> res;
    for (auto &[first, second] : freq)
    {
        if (second == max_freq)
            res.push_back({first, second});
    }
    return res;
}

int main()
{
    vector<int> numbers = {1, 1, 3, 5, 8, 9, 5, 8, 8, 5};
    vector<pair<int, int>> res = most_frequent(numbers);
    cout << "MOST FREQUENT ELEMENTS:\n";
    for (auto &[first, second] : res)
        cout << "{" << first << ", " << second << "}\n";
    return 0;
}