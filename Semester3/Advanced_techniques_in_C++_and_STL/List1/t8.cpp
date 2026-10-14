#include <iostream>
#include <vector>

using namespace std;

using pair_iterators = pair<vector<int>::const_iterator, vector<int>::const_iterator>;

pair_iterators find_range(const vector<int> &v, int target)
{
    auto left = v.begin();
    auto right = v.end();
    while (left < right)
    {
        auto mid = left + (right - left) / 2;
        if ((*mid <=> target) < 0)
            left = mid + 1;
        else right = mid;
    }
    auto first = left;

    right = v.end();
    while (left < right)
    {
        auto mid = left + (right - left) / 2;
        if ((*mid <=> target) <= 0)
            left = mid + 1;
        else right = mid;
    }

    return {first, left};
}

int main()
{
    vector<int> nums = {1, 2, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7, 7, 8, 9};

    auto [first1, last1] = find_range(nums, 5);
    for (auto it = first1; it != last1; it++)
        cout << *it << " ";
    cout << '\n';

    auto [first2, last2] = find_range(nums, 7);
    for (auto it = first2; it != last2; it++)
        cout << *it << " ";
    cout << '\n';
    return 0;
}