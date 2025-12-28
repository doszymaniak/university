#include <stdio.h>
#include "shop.h"

int main()
{
    int status = init();
    if (status != 0)
    {
        printf("MEMORY ALLOCATION ERROR!");
        return 1;
    }
    int c;
    while ((c = getchar()) != EOF)
    {
        if (c == 'I') info();
        else if (c == 'B')
        {
            int price, amount, index;
            if (scanf("%d %d %d", &price, &amount, &index) == 3) buy(index, amount, price);
            else getchar();
        }
        else if (c == 'S')
        {
            int amount, index;
            if (scanf("%d %d", &amount, &index) == 2) sell(index, amount);
            else getchar();
        }
    }
    return 0;
}
