#ifndef SHOP_H
#define SHOP_H

#define MARGIN 100
#define INIT 10000000
#define MAX_LNAME 100

struct product {
    char *name;
    int price;
    int amount;
};

extern long long budget;
extern struct product *products;

int init();
int buy(char *name, int amount, int price);
void sell(char *name, int amount);
void info();

#endif