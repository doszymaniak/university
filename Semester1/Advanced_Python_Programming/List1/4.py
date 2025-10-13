import random
import math

def przyblizenie_pi(losowania, eps):
    dlugosc_boku = 10
    promien = dlugosc_boku / 2
    aktualne_pi = 0
    licznik = 0
    trafienia = 0
    while licznik < losowania:
        x = random.uniform(0, dlugosc_boku)
        y = random.uniform(0, dlugosc_boku)
        if (x - promien)**2 + (y - promien)**2 <= promien**2:
            trafienia += 1
        licznik += 1
        aktualne_pi = 4 * trafienia / licznik
        print(f"Przyblizenie numer {licznik}: {aktualne_pi}")
        if abs(math.pi - aktualne_pi) < eps:
            print(f"Osiagnieto dokladnosc {eps} po {licznik} losowaniach")
            break

przyblizenie_pi(10, 0.00001)