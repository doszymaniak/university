import itertools

def sprawdz_rownanie(liczba1, liczba2, liczba3, op):
    liczba1 = int(liczba1)
    liczba2 = int(liczba2)
    liczba3 = int(liczba3)
    if op == "+":
        return liczba1 + liczba2 == liczba3
    elif op == "-":
        return liczba1 - liczba2 == liczba3
    elif op == "*":
        return liczba1 * liczba2 == liczba3
    return liczba2 != 0 and liczba1 / liczba2 == liczba3 and liczba1 % liczba2 == 0

def generuj_rozwiazanie(napis1, napis2, napis3, op):
    litery = ""
    for lit in napis1 + napis2 + napis3:
        if lit not in litery:
            litery += lit
    pierwsze = [napis1[0], napis2[0], napis3[0]]
    for perm in itertools.permutations("0123456789", len(litery)):
        podstawienie = {litera: cyfra for litera, cyfra in zip(litery, perm)}
        if any(podstawienie[pierwsza] == '0' for pierwsza in pierwsze):
            continue
        liczba1 = ''.join([podstawienie[lit] for lit in napis1])
        liczba2 = ''.join([podstawienie[lit] for lit in napis2])
        liczba3 = ''.join([podstawienie[lit] for lit in napis3])
        if sprawdz_rownanie(liczba1, liczba2, liczba3, op):
            yield podstawienie

def wyswietl_rozwiazanie(napis1, napis2, napis3, op, rozw):
    liczba1 = ''.join([rozw[lit] for lit in napis1])
    liczba2 = ''.join([rozw[lit] for lit in napis2])
    liczba3 = ''.join([rozw[lit] for lit in napis3])
    szerokosc = max(len(liczba1), len(liczba2), len(liczba3))
    print("------------")
    print(napis1.rjust(szerokosc))
    print(napis2.rjust(szerokosc) + " " + op)
    print('-' * (szerokosc + 2))
    print(napis3.rjust(szerokosc))
    print()
    print(liczba1.rjust(szerokosc))
    print(liczba2.rjust(szerokosc) + " " + op)
    print('-' * (szerokosc + 2))
    print(liczba3.rjust(szerokosc))


napis1 = "KIOTO"
napis2 = "OSAKA"
napis3 = "TOKIO"
op = "+"
for rozw in generuj_rozwiazanie(napis1, napis2, napis3, op):
    wyswietl_rozwiazanie(napis1, napis2, napis3, op, rozw)

napis1 = "SEND"
napis2 = "MORE"
napis3 = "MONEY"
op = "+"
for rozw in generuj_rozwiazanie(napis1, napis2, napis3, op):
    wyswietl_rozwiazanie(napis1, napis2, napis3, op, rozw)