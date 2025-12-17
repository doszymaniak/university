#include "primrepr.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

const unsigned char primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};

penumber new_penumber(unsigned long long n)
{
    if (n == 0) return NULL;
    penumber new_number = malloc(sizeof(struct penumber_struct));
    if (new_number == NULL) return NULL;
    for (int i = 0; i < 8; i++) (*new_number).arr[i] = 0;
    for (int i = 0; i < 8; i++)
    {
        while (n % primes[i] == 0) 
        {
            if ((*new_number).arr[i] == UCHAR_MAX)
            {
                free(new_number);
                return NULL;
            }
            (*new_number).arr[i]++;
            n /= primes[i];
        }
    }
    if (n != 1)
    {
        free(new_number);
        return NULL;
    }
    return new_number;
}

void del_penumber(penumber n)
{
    free(n);
}

void print_penumber(penumber n)
{
    bool not_printed = true;
    for (int i = 0; i < 8; i++)
    {
        if ((*n).arr[i] == 0) continue;
        if (not_printed == false) printf("x");
        printf("%u", primes[i]);
        if ((*n).arr[i] != 1) printf("^%u", (*n).arr[i]);
        not_printed = false;
    }
    if (not_printed)
    {
        printf("1");
        return;
    }
}

unsigned long long to_ull(penumber n)
{
    if (n == NULL) return 0;
    unsigned long long res = 1;
    for (int i = 0; i < 8; i++)
    {
        unsigned char exp = (*n).arr[i];
        for (unsigned char j = 0; j < exp; j++)
        {
            if (res > ULLONG_MAX / primes[i]) return 0;
            res *= primes[i];
        }
    }
    return res;
}

// 'n' divides 'm' if, for each 'i', the exponent of 'n' is less than or equal to
// the exponent of 'm'
int divides(penumber n, penumber m)
{
    if (n == NULL || m == NULL) return 0;
    for (int i = 0; i < 8; i++)
    {
        if ((*n).arr[i] > (*m).arr[i]) return 0;
    }
    return 1;
}

// Product - the addition of exponents
penumber pnprod(penumber n, penumber m)
{
    if (n == NULL || m == NULL) return NULL;
    penumber res = malloc(sizeof(struct penumber_struct));
    if (res == NULL) return NULL;
    for (int i = 0; i < 8; i++) 
    {
        if ((*n).arr[i] > UCHAR_MAX - (*m).arr[i])
        {
            free(res);
            return NULL;
        }
        (*res).arr[i] = (*n).arr[i] + (*m).arr[i];
    }
    return res;
}

// LCM - for each 'i', take the maximum exponent
penumber pnlcm(penumber n, penumber m)
{
    if (n == NULL || m == NULL) return NULL;
    penumber res = malloc(sizeof(struct penumber_struct));
    if (res == NULL) return NULL;
    for (int i = 0; i < 8; i++)
    {
        if ((*n).arr[i] > (*m).arr[i]) (*res).arr[i] = (*n).arr[i];
        else (*res).arr[i] = (*m).arr[i];
    }
    return res;
}

// GCD - for each 'i', take the minimum exponent
penumber pngcd(penumber n, penumber m)
{
    if (n == NULL || m == NULL) return NULL;
    penumber res = malloc(sizeof(struct penumber_struct));
    if (res == NULL) return NULL;
    for (int i = 0; i < 8; i++)
    {
        if ((*n).arr[i] < (*m).arr[i]) (*res).arr[i] = (*n).arr[i];
        else (*res).arr[i] = (*m).arr[i];
    }
    return res;
}

// Division - the subtraction of exponents
penumber pndiv(penumber n, penumber m)
{
    if (n == NULL || m == NULL) return NULL;
    if (!divides(m, n)) return NULL;
    penumber res = malloc(sizeof(struct penumber_struct));
    if (res == NULL) return NULL;
    for (int i = 0; i < 8; i++) (*res).arr[i] = (*n).arr[i] - (*m).arr[i];
    return res;
}