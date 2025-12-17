#include <stdio.h>
#include "primrepr.h"

void prettyprint_pn(char *msg, penumber pn)
{
    printf("Representation of %s: ", msg);
    if (pn == NULL) puts("does not exist");
    else
    {
        print_penumber(pn);
        putchar('\n');
    }
}

void prettyprint_ull(penumber pn)
{
    if (pn == NULL)
    {
        puts("Invalid arguments to 'prettyprint_ull'");
        return;
    }
    printf("The number represented by ");
    print_penumber(pn);
    unsigned long long out = to_ull(pn);
    if (out == 0) puts(" exceeds the type's range");
    else printf(" is %llu\n", out);
}

int main()
{
    penumber six = new_penumber(6);
    penumber hundred_32 = new_penumber(132);
    penumber twenty_9 = new_penumber(29);
    penumber big = new_penumber(2100000000);
    prettyprint_pn("6", six);
    prettyprint_pn("132", hundred_32);
    prettyprint_pn("29", twenty_9);
    
    penumber bigger = pnprod(big, big);
    penumber biggest = pnprod(bigger, bigger);
    prettyprint_ull(bigger);
    prettyprint_ull(biggest);

    if (six != NULL && hundred_32 != NULL && twenty_9 != NULL)
    {
        divides(six, twenty_9) ? puts("6 is a divisor of 29") : puts("6 is not a divisor of 29");
        divides(twenty_9, hundred_32) ? puts("29 is a divisor of 132") : puts("29 is not a divisor of 132");
    }

    penumber div1 = pndiv(hundred_32, six);
    penumber div2 = pndiv(hundred_32, twenty_9);
    prettyprint_pn("of the first division", div1);
    prettyprint_pn("of the second division", div2);

    del_penumber(six);
    del_penumber(twenty_9);
    del_penumber(hundred_32);
    del_penumber(big);
    del_penumber(bigger);
    del_penumber(biggest);
    del_penumber(div1);
    del_penumber(div2);
    return 0;
}