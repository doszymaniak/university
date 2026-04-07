# Lista 1

## Zadanie 1
a)
```ocaml
10;;
```
int = 10

b)
```ocaml
2 * 3 + 4;;
```
int = 10

c)
```ocaml
2 * (3 + 4);;
```
int = 14

d)
```ocaml
let a = 3;;
```
val a : int = 3

e)
```ocaml
let b = a + 1;;
```
val b : int = 4

f)
```ocaml
if b > a && b < a * b then b else a;;
```
int = 4

g)
```ocaml
2 + (if b > a then b else a);;
```
int = 6

h)
```ocaml
let a = if b * b > b then b else -1 in a * b;;
```
int = 16


## Zadanie 2
a)
```ocaml
"foo" ^ 42;;
```
Niepoprawne, konkatenacja dotyczy stringów

b)
```ocaml
"foo" ^ string_of_int 42;;
```
string = "foo42"

c)
```ocaml
1. = 2;;
```
Niepoprawne, porównanie floata z intem

d)
```ocaml
fun a -> a + 5;;
```
int -> int = `<fun>`

e)
```ocaml
fun a -> if a > b then a else "foo";;
```
Niepoprawne, typ zwracanej wartości musi być ten sam w obu przypadkach

f)
```ocaml
fun a b -> if a > 5 then a else b;;
```
int -> 'a -> int = `<fun>`

g)
```ocaml
fun a b ->
    let c = a = b in
    if a > 3 && b = "foo"
    then c
    else false;;
```
Niepoprawne, interpreter narzuca równość typów a i b, ale potem porównujemy b ze stringiem

h)
```ocaml
fun a ->
    let f a b = a * a + b * b in
    f (f a a) a;;
```
int -> int = `<fun>`

i)
```ocaml
let f a = a > 2 in if 3 > 2 then true else f (f 2);;
```
Niepoprawne, (f 2) jest typu bool, ale funkcja f wymaga, aby a było intem


## Zadanie 3
a)
```ocaml
x;;
```
`x` - wolna

b)
```ocaml
let x = 3 in x + y;;
```
`x` - związana w `x + y` (wyst. wiążące: `let x = 3`)\
`y` - wolna

c)
```ocaml
let x = 1
and y = x + 2
in x + y;;
```
`x` - związana w `x + y` (wyst. wiążące: `let x = 1`), wolna w `y = x + 2`\
`y` - związana w `x + y` (wyst. wiążące: `y = x + 2`)

d)
```ocaml
let x = 1 in
let y = x + 2 in
x + y;;
```
`x` - związana w `x + y` i w `let y = x + 2` (wyst. wiążące: `let x = 1`)\
`y` - związana w `x + y` (wyst. wiążące: `let y = x + 2`)

e)
```ocaml
let f x y = x * y * z;;
```
`x` - związana w `x * y * z` (wyst. wiążące: `let f x y`)\
`y` - związana w `x * y * z` (wyst. wiążące: `let f x y`)\
`z` - wolna

f)
```ocaml
let f x =
    let g y z = x * y * z in
g (h x) z;;
```
`x` - związana w `x * y * z` i `g (h x) z` (wyst. wiążące: `let f x`)\
`y` - związana w `x * y * z` (wyst. wiążące: `let g y z`)\
`z` - związana w `x * y * z` (wyst. wiążące: `let g y z`), wolna w `g (h x) z`\
`h` - wolna


## Zadanie 4
```ocaml
let max_two_square x y z =
  let (num, smaller) = if x > y then (x, y) else (y, x) in
  if smaller > z then num * num + smaller * smaller else
  num * num + z * z;;
```

## Zadanie 5
```ocaml
let a_plus_abs_b a b =
    (if b > 0 then (+) else (-)) a b
```
Funkcja zwraca sumę a i wartości bezwzględnej z b.\
Zgodnie z definicją, jeśli b > 0, to dodaje te liczby,
a w przeciwnym przypadku odejmuje.


## Zadanie 6
```ocaml
let rec f () = f ()

let test x y =
    if x = 0 then 0 else y
```
Sprawdzenie kolejności obliczania przez interpreter:
```ocaml
test 0 (f ())
```
Jeśli funkcja zwróciłaby 0, oznaczałoby to, że jej argumenty obliczane są dopiero, gdy są potrzebne (leniwa ewaluacja).\
Jednak funkcja zapętliła się, więc wpadła w nieskończoną rekursję już przy wywołaniu, co oznacza, że obliczenia wykonywane są gorliwie.