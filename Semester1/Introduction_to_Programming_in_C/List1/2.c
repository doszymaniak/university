#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int n, result = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        char string_curr[50], reversed_curr[50];
        sprintf(string_curr, "%d", i);
        int idx = 0;
        for (int j = strlen(string_curr) - 1; j >= 0; j--)
        {
            reversed_curr[idx] = string_curr[j];
            idx++;
        }
        reversed_curr[idx] = '\0';
        if (reversed_curr[0] == '0') continue;

        long long sum = atoi(string_curr) + atoi(reversed_curr);
        bool stop = false;
        while (sum > 0)
        {
            int digit = sum % 10;
            if (digit % 2 == 0) 
            {
                stop = true;
                break;
            }
            sum /= 10;
        }
        if (stop) continue;
        result++;
    }
    printf("%d\n", result);
    return 0;
}