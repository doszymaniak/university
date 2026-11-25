#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> permutations(string &word)
{
    sort(word.begin(), word.end());
    vector<string> res;
    while (true)
    {
        res.push_back(word);
        if (!next_permutation(word.begin(), word.end()))
            break;
    }
    return res;
}

int main()
{
    string word = "lampa";

    vector<string> res = permutations(word);

    for (auto &perm : res)
        cout << perm << '\n';
    return 0;
}