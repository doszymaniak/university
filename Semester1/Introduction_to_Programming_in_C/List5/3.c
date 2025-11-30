#include <stdio.h>

#define N 2007
#define MOD 1000000000
#define ll long long

int memo[N][N];

int solve(int x, int y)
{
    if (memo[x][y] != -1) return memo[x][y];
    ll res = 0;
    if (x == 0 && y == 0) res = 1;
    else if (x <= 2) res = solve(x + y - 1, 0);
    else if (x > 2 && y % 2 == 0) res = solve(x - 3, y + 3) + solve(x - 1, y);
    else res = solve(x + 1, y - 1) + solve(x, y - 1);
    res %= MOD;
    memo[x][y] = res;
    return memo[x][y];
}

void precompute()
{
    for (int sum = 0; sum <= 2000; sum++)
    {
        for (int x = 0; x <= 1000; x++)
        {
            int y = sum - x;
            if (y < 0 || y > 1000) continue;
            solve(x, y);
        }
    }
}

int main()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) memo[i][j] = -1;
    precompute();
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", solve(x, y));
    }
    return 0;
}