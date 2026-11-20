var n = 1;

console.log(typeof n)

// Prototyp obiektu opakowujacego liczbe, czyli Number.prototype
console.log(typeof Object.getPrototypeOf(n));

// Czy mozna dodawac dowolne pola/funkcje do wartosci prostych?
// Nie, wartosci typow prostych nie sa obiektami

// Utworzenie tymczasowego obiektu opakowujacego typu Number
// Wlaciwosc "foo" zostaje przypisana do tymczasowego obiektu, po czym
// zostaje on odrzucony
n.foo = 'foo';

// Przy odczycie n.foo tworzony jest kolejny tymczasowy obiekt, ktory
// nie zawiera wlasciwosci "foo", dlatego dostajemy undefined
console.log(n.foo);