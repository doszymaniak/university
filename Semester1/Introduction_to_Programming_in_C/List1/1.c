#include <stdio.h>
#include <stdbool.h>

int main()
{
    int pola_poziom, pola_pion, znaki_poziom, znaki_pion, lewe; 
    scanf("%d %d %d %d %d", &pola_poziom, &pola_pion, &znaki_poziom, &znaki_pion, &lewe);
    if (pola_poziom <= 0 || pola_pion <= 0 || znaki_poziom <= 0 || znaki_pion <= 0)
    {
        printf("Pierwsze cztery wczytane liczby musza byc dodatnie!\n");
        return 1;
    }
    if (lewe != 0 && lewe != 1)
    {
        printf("Ostatnia liczba musi byc rowna 0 lub 1!\n");
        return 1;
    }
    
    bool czy_wypelniamy_pierwsze = lewe, czy_wypelniamy_akt = lewe;
    int licznik_pion = 0, licznik_poziom = 0;
    for (int i = 0; i < pola_pion * znaki_pion; i++)
    {
        licznik_poziom = 0;
        for (int j = 0; j < pola_poziom * znaki_poziom; j++)
        {
            if (czy_wypelniamy_akt) putchar('#');
            else putchar(' ');
            licznik_poziom++;
            if (licznik_poziom % znaki_poziom == 0)
            {
                if (czy_wypelniamy_akt) czy_wypelniamy_akt = false;
                else czy_wypelniamy_akt = true;
            }
        }
        licznik_pion++;
        if (licznik_pion % znaki_pion == 0)
        {
            if (czy_wypelniamy_pierwsze) czy_wypelniamy_pierwsze = false;
            else czy_wypelniamy_pierwsze = true;
        }
        czy_wypelniamy_akt = czy_wypelniamy_pierwsze;
        putchar('\n');
    }
}