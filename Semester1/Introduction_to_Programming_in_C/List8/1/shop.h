#ifndef SHOP_H
#define SHOP_H

#define MARGIN 100
#define INIT 10000000
#define MAX_PROD 10

struct product {
    int price;
    int amount;
};

extern long long budget;
extern struct product *products;

int init();
void buy(int index, int amount, int price);
void sell(int index, int amount);
void info();

#endif