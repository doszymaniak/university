#include <stdio.h>
#include <stdbool.h>

int n;
int arr[200007];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%1d", &arr[i]);
        bool ok = true;
        if (n == 3)
        {
            if (arr[0] == 1 && arr[1] == 0 && arr[2] == 1) printf("NIE\n");
            else printf("TAK\n");
            continue;
        }
        int last = -2;
        for (int i = 0; i < n; i++)
        {
            if (i + 2 >= n) break;
            if (arr[i] == 1 && arr[i + 1] == 0 && arr[i + 2] == 1)
            {
                bool left = (i - 1 >= 0 && arr[i - 1] == 0 && last != i - 1) ? 1 : 0;
                bool right = (i + 3 < n && arr[i + 3] == 0) ? 1 : 0;
                if (left || right) 
                {
                    if (right) last = i + 3;
                    i += 2;
                    continue;
                }
                else
                {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) printf("TAK\n");
        else printf("NIE\n");
    }
    return 0;
}