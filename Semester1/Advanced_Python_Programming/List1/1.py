import decimal as d

def typ_suma(el):
    if isinstance(el, float):
        return 0
    else:
        return d.Decimal('0')

def typ_procent(el):
    if isinstance(el, float):
        return 0.23
    else:
        return d.Decimal('0.23')

def vat_faktura(lista):
    suma = typ_suma(lista[0])
    procent = typ_procent(lista[0])
    for element in lista:
        suma += element
    return suma * procent

def vat_paragon(lista):
    suma = typ_suma(lista[0])
    procent = typ_procent(lista[0])
    for element in lista:
        suma += (element * procent)
    return suma

def test(lista):
    print("Lista: " + str(lista))
    print("Wartosc vat_faktura: " + str(vat_faktura(lista)))
    print("Wartosc vat_paragon: " + str(vat_paragon(lista)))
    print("Wynik porownania: " + str(vat_faktura(lista) == vat_paragon(lista)))

lista1 = [0.33, 9.44, 0.67, 0.99]
print("TEST BEZ UZYCIA DECIMAL")
test(lista1)

lista2 = [d.Decimal('0.33'), d.Decimal('9.44'), d.Decimal('0.67'), d.Decimal('0.99')]
print("\nTEST Z UZYCIEM DECIMAL")
test(lista2)