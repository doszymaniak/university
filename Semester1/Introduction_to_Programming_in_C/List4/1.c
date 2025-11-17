#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARG_LEN 30
#define MAX_N 100
#define ll long long 

// C(n) = sum(0...(n - 1)) C(i) * C(n - i - 1)
ll catalan_rec(int n)
{
    if (n == 0) return 1;
    ll res = 0;
    for (int i = 0; i < n; i++) res += catalan_rec(i) * catalan_rec(n - i - 1);
    return res;
}

ll catalan_memo(int n)
{
    ll memo[MAX_N] = {0};
    memo[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++) memo[i] += memo[j] * memo[i - j - 1];
    }
    return memo[n];
}

// C(n) = 2 * (2 * n - 1) / (n + 1) * C(n - 1)
ll catalan_second(int n)
{
    if (n == 0) return 1;
    ll prev = catalan_second(n - 1);
    return prev * 2 * (2 * n - 1) / (n + 1);
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("TOO FEW ARGUMENTS!\n");
        return 1;
    }
    if (argc > 3)
    {
        printf("TOO MANY ARGUMENTS!\n");
        return 1;
    }
    // If the user provides a flag as the first argument, we swap it with 'n'
    // This works because '-' has a lower ASCII value than any digit
    if (argc == 3 && strcmp(argv[1], argv[2]) < 1)
    {
        char temp[MAX_ARG_LEN];
        strcpy(temp, argv[1]);
        strcpy(argv[1], argv[2]);
        strcpy(argv[2], temp);
    }
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("N MUST BE AN INTEGER!\n");
            return 1;
        }
    }
    int n = atoi(argv[1]);
    if (n < 0)
    {
        printf("N MUST BE NON-NEGATIVE!\n");
        return 1;
    }
    if (n > MAX_N)
    {
        printf("N IS TOO LARGE!\n");
        return 1;
    }
    if (argc == 2 || strcmp(argv[2], "-m") == 0)
    {
        printf("USING MEMOIZATION: \n");
        printf("%lld\n", catalan_memo(n));
    }
    else if (strcmp(argv[2], "-n") == 0)
    {
        printf("USING RECURSION: \n");
        printf("%lld\n", catalan_rec(n));
    }
    else if (strcmp(argv[2], "-f") == 0)
    {
        printf("USING THE SECOND FORMULA: \n");
        printf("%lld\n", catalan_second(n));
    }
    else 
    {
        printf("INVALID FLAG!\n");
        return 1;
    }
    return 0;
}