def sudan(n, x, y):
    if n == 0: 
        return x + y
    if y == 0:
        return x
    part_res = sudan(n, x, y - 1)
    return sudan(n - 1, part_res, part_res + y)

data = {}

def sudan_memo(n, x, y):
    key = (n, x, y)
    if key in data:
        return data[key]
    
    result = 0
    if n == 0:
        result = x + y
    elif y == 0: 
        result = x
    else:
        part_res = sudan_memo(n, x, y - 1)
        result = sudan_memo(n - 1, part_res, part_res + y)
    data[key] = result
    return data[key]

def test(n, x, y):
    data.clear()
    print(f"TEST DLA N = {n}, X = {x}, Y = {y}")
    print(f"Z ZAPAMIETYWANIEM: {sudan_memo(n, x, y)}")
    print(f"BEZ ZAPAMIETYWANIA: {sudan(n, x, y)}\n")

# test(1, 4, 5)
# test(0, 5, 10)
# test(2, 4, 2)
# test(3, 1, 1)
# test(2, 5, 3)
# test(1, 700, 700)
# test(2, 2, 2)
# test(4, 0, 0)
test(2, 3, 2)

# Dla n = 0 i n = 1 obie wersje dzialaja sensownie dla duzych x i y
# Dla n = 2 obie wersje dzialaja dla x <= 2 i y <= 2
# Dla n = 3 obie wersje dzialaja dla x = 1 i y = 1
# Wpp problemem nie jest efektywnosc obliczen, a gleboki stos wywolan, poniewaz
# funkcja rosnie zbyt szybko