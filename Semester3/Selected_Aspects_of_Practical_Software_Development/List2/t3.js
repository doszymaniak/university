console.log((![] + [])[+[]] + (![] + [])[+!+[]] + ([![]] + [][[]])[+!+[] + [+[]]] + (![] + [])[!+[] + !+[]]);

/*
![] -> false
[] -> "" podczas konwersji tablicy na napis
+ (2 argumenty) -> sprawdza, czy ktorys z operandow jest napisem
+ (1 argument) -> wymusza konwersje na liczbe

Grupa 1
(![] + [])[+[]]
Pierwszy nawias: ![] + [] -> false + "" -> "false" + "" -> "false"
Drugi nawias: +[] -> +"" -> 0
Skladajac: ("false")[0] -> "false"[0] -> 'f'

Grupa 2
(![] + [])[+!+[]]
Pierwszy nawias: ![] + [] -> false + "" -> "false" + "" -> "false"
Drugi nawias: +(!(+[])) -> +(!0) -> +(true) -> 1
Skladajac: ("false")[1] -> "false"[1] -> 'a'

Grupa 3
([![]] + [][[]])[+!+[] + [+[]]]
Pierwszy nawias: [![]] + [][[]]
Lewa: [![]] -> [false]
Prawa - indeksowanie tablicy, wewnetrzna pelni funkcje indeksu: [][[]] -> [][""] -> undefined
Skladajac pierwszy nawias: [false] + undefined -> "false" + "undefined" -> "falseundefined" 
Drugi nawias: +!+[] + [+[]]
Lewa: +!+[] -> +!0 -> +1 -> 1
Prawa: [+[]] -> [0]
Skladajac: 1 + [0] -> "1" + "0" -> "10"
Czyli skladajac wszystko: "falseundefined"["10"] -> 'i'

Grupa 4
(![] + [])[!+[] + !+[]]
Pierwszy nawias: ![] + [] -> false + [] -> "false" + "" -> "false"
Drugi nawias: !+[] + !+[]
Lewa: !0 -> true
Prawa: !0 -> true
Skladajac: true + true -> 2, bo zaden operand nie jest napisem, wiec wykonuje sie dodawanie numeryczne
Skladajac wszystko: "false"[2] -> 'l'

Ostatecznie skladajac wszystkie grupy: 'f' + 'a' + 'i' + 'l' -> "fail"
*/