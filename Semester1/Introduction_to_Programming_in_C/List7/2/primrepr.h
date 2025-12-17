#ifndef PRIMEREPR_H
#define PRIMEREPR_H

struct penumber_struct {
    unsigned char arr[8];
};

typedef struct penumber_struct *penumber;

penumber new_penumber(unsigned long long n);
void del_penumber(penumber n);
void print_penumber(penumber n);
unsigned long long to_ull(penumber n);
int divides(penumber n, penumber m);
penumber pnprod(penumber n, penumber m);
penumber pnlcm(penumber n, penumber m);
penumber pngcd(penumber n, penumber m);
penumber pndiv(penumber n, penumber m);

#endif