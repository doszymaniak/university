var Person = function (name, surname) {
    this.name = name;
    this.surname = surname;
}

Person.prototype.say = function () {
    return `${this.name} ${this.surname}`;
}

var Worker = function (name, surname, age) {
    // wywolanie bazowej funkcji konstruktorowej
    Person.call(this, name, surname);
    this.age = age;
}

// Powiazanie lancucha prototypow
// Tworzymy nowy, pusty obiekt, ktorego prototypem jest Person.prototype
// Obiekty utworzone przez Worker dziedzicza metody z Person.prototype
// Dodawanie lub nadpisywanie metod w Worker.prototype nie zmienia prototypu klasy bazowej
// Nie tworzymy dodatkowej instancji Person
// Lancuch prototypow: w -> Worker.prototype -> Person.prototype -> Object.prototype -> null
Worker.prototype = Object.create(Person.prototype);

// Bledne podejscie 1: Worker.prototype = Person.prototype
// Oba obiekty wspoldziela ten sam prototyp i nie sa od siebie niezalezne
// Oznacza to, ze jesli nadpiszemy metode w prototypie Worker, to nadpiszemy ja rowniez
// w Person i na odwrot
// Nie dostajemy prawdziwego dziedziczenia

// Bledne podejscie 2: Worker.prototype = new Person();
// Niepotrzebne wywolanie konstruktora bazowego, niepotrzebne tworzenie instacji
// klasy bazowej
// Wlasciwosci zdefiniowane w konstruktorze Person znajda sie na obiekcie prototypowym
// i beda wspoldzielone przez wszystkie obiekty Worker, ktore nie maja wlasnych wlasciwosci
// o tych samych nazwach

Worker.prototype.say = function () {
    // wywolanie metody z klasy bazowej
    var _ = Person.prototype.say.call(this);
    return `${_} ${this.age}`;
}

var w = new Worker('jan', 'kowalski', 48);
console.log(w.say());
var p = new Person('jan', 'kowalski');
console.log(p.say()); 