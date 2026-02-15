// https://codeforces.com/problemset/problem/230/B

#include <bits/stdc++.h>

using namespace std;

const int MAX_NUM = 1e6;
vector<bool> sieve(MAX_NUM + 1, true);

void find_primes()
{
    sieve[0] = 0;
    sieve[1] = 0;
    for (int i = 2; i * i <= MAX_NUM; i++)
    {
        for (int j = i * i; j <= MAX_NUM; j += i) sieve[j] = false;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    find_primes();
    for (int i = 0; i < n; i++)
    {
        long long num;
        cin >> num;
        long long sq = sqrt(num);
        if (sq * sq == num && sieve[sq]) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}