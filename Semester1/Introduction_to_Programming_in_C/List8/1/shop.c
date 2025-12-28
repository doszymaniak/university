#include "shop.h"
#include <stdlib.h>
#include <stdio.h>

long long budget;
struct product *products;

int init()
{
    budget = INIT;
    products = malloc(MAX_PROD * sizeof(struct product));
    if (products == NULL) return 1;
    for (int i = 0; i < MAX_PROD; i++) 
    {
        products[i].price = 0;
        products[i].amount = 0;
    }
    return 0;
}

void buy(int index, int amount, int price)
{
    if (index < 0 || index >= MAX_PROD) return;
    if (price < 0) return;
    if (amount < 0) return;
    struct product *curr_product = &products[index];
    long long cost = (long long)amount * price;
    if (budget < cost) return;
    budget -= cost;
    curr_product->amount += amount;
    curr_product->price = price;
}

void sell(int index, int amount)
{
    if (index < 0 || index >= MAX_PROD) return;
    if (amount < 0) return;
    struct product *curr_product = &products[index];
    if (curr_product->amount < amount) return;
    curr_product->amount -= amount;
    budget += ((long long)curr_product->price * amount * (100 + MARGIN) / 100);
}

void info()
{
    printf("CURRENT BUDGET: %lld\n", budget);
}