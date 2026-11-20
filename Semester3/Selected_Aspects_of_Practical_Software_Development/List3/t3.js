// W kazdej iteracji petli tworzona jest funkcja, ktora zwraca wartosc i
// Funkcje sa zapisywane w tablicy, ktora jest zwracana na koncu
// Te funkcje nie sa wykonywane w trakcie petli, sa tylko tworzone
// var ma zasieg funkcyjny, dlatego wszystkie funkcje korzystaja z tej samej zmiennej i
// Dopiero podczas wywolania funkcji odczytywana jest aktualna wartosc i
function createFs_var(n) {
    var fs = [];
    for (var i = 0; i < n; i++) {
        fs[i] =
            function () {
                return i;
            };
    };
    return fs;
}

// W petli for let tworzy osobna zmienna i dla kazdej iteracji
// Kazda funkcja ma dostep do wlasnej zmiennej i
// Po wywolaniu funkcji zwracana jest wartosc i z konkretnej iteracji
function createFs_let(n) {
    let fs = [];
    for (let i = 0; i < n; i++) {
        fs[i] =
            function () {
                return i;
            };
    };
    return fs;
}

// Aktualna wartosc i w petli zostaje przekazana jako argument a do createFunction
// Kazde wywolanie createFunction tworzy wlasne srodowisko zmiennych
function createFs_varOk(n) {
    var fs = [];
    function createFunction(a) {
        return function () { return a };
    }
    for (var i = 0; i < n; i++) {
        fs[i] = createFunction(i);
    };
    return fs;
}


console.log("createFs_var");
var myfs_var = createFs_var(10);
console.log(myfs_var[0]());
console.log(myfs_var[2]());
console.log(myfs_var[7]());

console.log("\ncreateFs_varOk");
var myfs_varOk = createFs_varOk(10);
console.log(myfs_varOk[0]());
console.log(myfs_varOk[2]());
console.log(myfs_varOk[7]());

console.log("\ncreateFs_let")
let myfs_let = createFs_let(10);
console.log(myfs_let[0]());
console.log(myfs_let[2]());
console.log(myfs_let[7]());