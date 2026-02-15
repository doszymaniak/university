// https://codeforces.com/problemset/problem/1725/B

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, d;
    cin >> n >> d;
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        arr.push_back(a);
    }
    sort(arr.begin(), arr.end());
    int wins = 0;
    int i = 0, j = arr.size() - 1;
    while (i <= j)
    {
        int curr_sum = arr[j];
        int how_many = d / curr_sum + 1;
        if (i + how_many - 1 <= j)
        {
            wins++;
            i += (how_many - 1);
            j--;
        }
        else break;
    }
    cout << wins << '\n';
}