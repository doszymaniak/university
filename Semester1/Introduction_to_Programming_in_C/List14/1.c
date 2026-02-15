#include <stdio.h>

#define ll long long

int main()
{
    int n, m, bricks, shots, box_size;
    scanf("%d %d %d %d %d", &n, &m, &bricks, &shots, &box_size);
    int arr[n + 1][m + 1];
    ll pref[n + 1][m + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++) 
        {
            arr[i][j] = 0;
            pref[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) scanf("%d", &arr[i][j]);
    for (int i = 0; i < shots; i++)
    {
        char com;
        int idx, h;
        scanf(" %c %d %d", &com, &idx, &h);
        int row, col;
        if (com == 'N') 
        {
            col = idx;
            row = 1;
        }
        else if (com == 'W')
        {
            row = idx;
            col = 1;
        }
        else if (com == 'S')
        {
            col = idx;
            row = n;
        }
        else 
        {
            row = idx;
            col = m;
        }
        int cnt = bricks;
        while (cnt > 0 && col >= 1 && col <= m && row >= 1 && row <= n)
        {
            if (arr[row][col] < h)
            {
                if (com == 'N') row++;
                else if (com == 'S') row--;
                else if (com == 'W') col++;
                else if (com == 'E') col--;
                continue;
            }
            if (arr[row][col] >= h)
            {
                arr[row][col]--;
                cnt--;
            }
            if (com == 'N') row++;
            else if (com == 'S') row--;
            else if (com == 'W') col++;
            else if (com == 'E') col--;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            pref[i][j] = arr[i][j];
            if (i > 1) pref[i][j] += pref[i - 1][j];
            if (j > 1) pref[i][j] += pref[i][j - 1];
            if (i > 1 && j > 1) pref[i][j] -= pref[i - 1][j - 1];
        }
    }
    ll max_sum = -1;
    for (int r1 = 1; r1 <= n - box_size + 1; r1++)
    {
        int r2 = r1 + box_size - 1;
        for (int c1 = 1; c1 <= m - box_size + 1; c1++)
        {
            int c2 = c1 + box_size - 1;
            ll curr_sum = pref[r2][c2] - pref[r1 - 1][c2] - pref[r2][c1 - 1] + pref[r1 - 1][c1 - 1];
            if (curr_sum > max_sum) max_sum = curr_sum;
        }
    }
    printf("%lld\n", max_sum);
    return 0;
}