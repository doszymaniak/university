// typeof zwraca stringa opisujacego typ operandu
console.log(typeof 'something'); // "string"
console.log(typeof 67); // "number"
console.log(typeof true); // "boolean"
console.log(typeof undefined); // "undefined"
console.log(typeof { age: 67 }); // "object"
console.log(typeof null); // "object"
console.log(typeof function () { }); // "function"
console.log(typeof [1, 2, 3]); // "object"

// instanceof sprawdza, czy obiekt jest instancja danego konstruktora lub klasy
console.log([1, 2, 3] instanceof Array); // true
console.log([1, 2, 3] instanceof Object); // true
console.log({ age: 67 } instanceof Array); // false
console.log(new Date() instanceof Date); // true