#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n;
    scanf("%d", &n);
    unsigned long long balls[n];
    for (int i = 0; i < n; i++) scanf("%llu", &balls[i]);
    // A bitmask determines which balls are chosen
    int res = 0;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        bool next = true;
        unsigned long long colors_used = 0;
        int curr_res = 0;
        for (int i = 0; i < n; i++)
        {
            // If we take the current ball
            if (mask & (1 << i))
            {
                // Check if any color was used earlier
                if ((balls[i] & colors_used) != 0)
                {
                    next = false;
                    break;
                }
                // If the color was not used earlier, merge bits using the OR operator
                colors_used |= balls[i];
                curr_res++;
            }
            if (!next) break;
        }
        if (curr_res > res) res = curr_res;
    }
    printf("%d\n", res);
    return 0;
}