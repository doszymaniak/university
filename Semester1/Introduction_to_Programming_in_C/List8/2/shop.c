#include "shop.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

long long budget;
struct product *products;
int products_n = 0, products_size = 0;

int init()
{
    budget = INIT;
    products = malloc(sizeof(struct product) * 10);
    if (!products) 
    {
        #ifdef DEBUG
        printf("MEMORY ALLOCATION ERROR\n");
        #endif
        return 1;
    }
    products_size = 10;
    return 0;
}

int buy(char *name, int amount, int price)
{
    int prod_idx = 0;
    for (int i = 0; i < products_n; i++)
    {
        struct product *curr = &products[i];
        if (strcmp(curr->name, name) == 0) break;
        prod_idx++;
    }
    if (prod_idx < products_n)
    {
        struct product *curr = &products[prod_idx];
        curr->price = price;
        curr->amount += amount;
        long long cost = price * amount;
        budget -= cost;
        #ifdef DEBUG
        printf("%d MORE PRODUCTS HAVE BEEN BOUGHT!\n", amount);
        long long old_budget = budget + cost;
        printf("OLD BUDGET: %lld\n", old_budget);
        info();
        #endif
        return 0;
    }
    if (products_n == products_size)
    {
        struct product *tmp = realloc(products, products_size * 2);
        if (!tmp) return 1;
        products = tmp;
        products_size *= 2;
        #ifdef DEBUG
        printf("THE SIZE OF THE PRODUCTS ARRAY HAS BEEN INCREASED\n");
        #endif
    }
    struct product *new = &products[prod_idx];
    new->name = malloc(sizeof(char) * MAX_LNAME);
    if (!new->name) return 1;
    strcpy(new->name, name);
    new->price = price;
    new->amount = amount;
    long long cost = price * amount;
    budget -= cost;
    products_n++;
    #ifdef DEBUG
    printf("A NEW ITEM HAS BEEN ADDED!\n");
    long long old_budget = budget + cost;
    printf("OLD BUDGET: %lld\n", old_budget);
    info();
    #endif
    return 0;
}

void sell(char *name, int amount)
{
    if (amount < 0) 
    {
        #ifdef DEBUG
        printf("THE PROVIDED AMOUNT IS LESS THAN ZERO\n");
        #endif
        return;
    }
    int prod_idx = 0;
    for (int i = 0; i < products_n; i++)
    {
        struct product *curr = &products[i];
        if (strcmp(curr->name, name) == 0) break;
        prod_idx++;
    }
    if (prod_idx == products_n) 
    {
        #ifdef DEBUG
        printf("THE PROVIDED ITEM DOES NOT EXIST IN THE PRODUCTS ARRAY\n");
        #endif
        return;
    }
    struct product *curr = &products[prod_idx];
    if (curr->amount < amount) 
    {
        #ifdef DEBUG
        printf("NOT ENOUGH PRODUCTS TO SELL\n");
        #endif
        return;
    }
    curr->amount -= amount;
    budget += ((long long)curr->price * amount * (100 + MARGIN) / 100);
    #ifdef DEBUG
    printf("%d PRODUCTS HAVE BEEN SOLD\n", amount);
    long long old_budget = budget - ((long long)curr->price * amount * (100 + MARGIN) / 100);
    printf("OLD BUDGET: %lld\n", old_budget);
    info();
    #endif
    if (curr->amount == 0)
    {
        free(curr->name);
        if (prod_idx != products_n - 1) products[prod_idx] = products[products_n - 1];
        products_n--;
        #ifdef DEBUG
        printf("ALL PRODUCTS OF THIS KIND HAVE BEEN SOLD\n");
        #endif
    }
}

void info()
{
    printf("CURRENT BUDGET: %lld\n", budget);
}