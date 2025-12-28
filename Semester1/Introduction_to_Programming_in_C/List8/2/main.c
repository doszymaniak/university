#include <stdio.h>
#include "shop.h"

int main()
{
    int status = init();
    if (status != 0)
    {
        printf("MEMORY ALLOCATION ERROR!\n");
        return 1;
    }
    int c;
    while ((c = getchar()) != EOF)
    {
        if (c == 'I') info();
        else if (c == 'B')
        {
            int price, amount;
            char name[MAX_LNAME + 1];
            if (scanf("%d %d", &price, &amount) == 2) 
            {
                int ch;
                while ((ch = getchar()) == ' ');
                char *ptr = name;
                *ptr++ = ch;
                while ((ch = getchar()) != '\n' && ptr < name + MAX_LNAME) *ptr++ = ch;
                *ptr = '\0';
                status = buy(name, amount, price);
                if (status) printf("MEMORY ALLOCATION ERROR\n");
            }
            else getchar();
        }
        else if (c == 'S')
        {
            int amount;
            char name[MAX_LNAME + 1];
            if (scanf("%d", &amount) == 1) 
            {
                int ch;
                while ((ch = getchar()) == ' ');
                char *ptr = name;
                *ptr++ = ch;
                while ((ch = getchar()) != '\n' && ptr < name + MAX_LNAME) *ptr++ = ch;
                *ptr = '\0';
                sell(name, amount);
            }
            else getchar();
        }
    }
    return 0;
}