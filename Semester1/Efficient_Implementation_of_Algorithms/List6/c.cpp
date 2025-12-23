// https://codeforces.com/problemset/problem/1025/B

#include <bits/stdc++.h>

using namespace std;

void prime_factorization(set<int> &s, int num)
{
    for (int i = 2; i * i <= num; i++)
    {
        while (num % i == 0)
        {
            s.insert(i);
            num /= i;
        }
    }
    if (num > 1) s.insert(num);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, a, b;
    cin >> n >> a >> b;
    n--;
    set<int> tmp1, tmp2;
    prime_factorization(tmp1, a);
    prime_factorization(tmp2, b);
    set<int> common = tmp1;
    common.insert(tmp2.begin(), tmp2.end());

    while (n--)
    {
        cin >> a >> b;
        set<int>::iterator it = common.begin();
        while (it != common.end())
        {
            if (a % *it == 0 || b % *it == 0) it++;
            else it = common.erase(it);
        }
    }

    if (common.size()) cout << *common.begin() << '\n';
    else cout << -1 << '\n';
    return 0;
}