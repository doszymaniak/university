from math import sqrt
import timeit

def pierwsze_imperatywna(n):
    lista = [] 
    for akt in range(2, n + 1):
        zla = False
        for dzielnik in range(2, int(sqrt(akt)) + 1):
            if akt % dzielnik == 0:
                zla = True
                break
        if not zla:
            lista.append(akt)
    return lista 
    """
    sito = (n + 1) * [True]
    sito[0] = sito[1] = False
    for i in range(2, int(sqrt(n)) + 1):
        for j in range(i * i, n + 1, i):
            sito[j] = False
    lista = []
    for i in range(2, n + 1):
        if sito[i]:
            lista.append(i)
    return lista
    """

def pierwsze_skladana(n):
    lista = range(2, n + 1)
    lista = [x for x in lista if 0 not in [x % y for y in range(2, int(sqrt(x)) + 1)]]
    return lista

def pierwsze_funkcyjna(n):
    lista = range(2, n + 1)
    lista = filter(lambda x : all(x % y != 0 for y in range(2, int(sqrt(x)) + 1)), lista)
    return list(lista)

def wyswietl_tabele(poc, kon, krok):
    funkcje = [
        ("imperatywna", pierwsze_imperatywna),
        ("skladana", pierwsze_skladana),
        ("funkcyjna", pierwsze_funkcyjna)
    ]
    naglowek = "n".rjust(6)
    for (nazwa, _) in funkcje:
        naglowek += f"{nazwa:>15}"
    print(naglowek)
    for n in range(poc, kon + 1, krok):
        wiersz = f"{n:>6}"
        for (_, fun) in funkcje:
            t1 = timeit.default_timer()
            fun(n)
            t2 = timeit.default_timer()
            czas = t2 - t1
            wiersz += f"{czas:>15.3f}"
        print(wiersz)
            

n = 20
print(f"WYNIK WERSJI IMPERATYWNEJ: {pierwsze_imperatywna(n)}")
print(f"WYNIK WERSJI Z LISTA SKLADANA: {pierwsze_skladana(n)}")
print(f"WYNIK WERSJI FUNKCYJNEJ: {pierwsze_funkcyjna(n)}")
print()

wyswietl_tabele(10000, 100000, 10000)
