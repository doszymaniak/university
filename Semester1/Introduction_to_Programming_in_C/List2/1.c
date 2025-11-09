#include <stdio.h>

int main()
{
    printf("Enter the number of columns: ");
    int n;
    if (scanf("%d", &n) != 1) 
    {
        printf("The number of columns must be an integer!\n");
        return 1;
    }
    if (n <= 0) 
    {
        printf("The number of columns must be greater than zero!\n");
        return 1;
    }
    printf("Enter the number of asterisks in column i: ");
    int a[n + 1], len = 0;
    for (int i = 1; i <= n; i++)
    {
        if (scanf("%d", &a[i]) != 1)
        {
            printf("The number of asterisks must be an integer!\n");
            return 1;
        }
        if (a[i] < 0) 
        {
            printf("The number of asterisks must be zero or greater!\n");
            return 1;
        }
        if (len < a[i]) len = a[i];
    }
    
    char arr[n + 1][len + 1];
    for (int i = 1; i <= n; i++)
    {
        int to_print = a[i];
        int space = (len / 2) - (to_print / 2);
        for (int j = 1; j <= len; j++)
        {
            if (space) 
            {
                arr[i][j] = '.';
                space--;
                continue;
            }
            if (to_print) 
            {
                arr[i][j] = '*';
                to_print--;
                continue;
            }
            arr[i][j] = '.';
        }
    }
    
    for (int i = 1; i <= len; i++)
    {
        for (int j = 1; j <= n; j++) printf("%c", arr[j][i]);
        printf("\n");
    }
    return 0;
}