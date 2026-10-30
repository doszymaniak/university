console.log("1. . OPERATOR AND [] OPERATOR");

const person = {
    name: "Jan",
    age: 20
};

console.log(person.name); // Jan
console.log(person["name"]); // Jan
const key = "age";
console.log(person[key]); // 20
console.log(person.key); // undefined
person.age = 21;
person["name"] = "Anna";
console.log(person); // { name: 'Anna', age: 21 }


console.log("\n2. OBJECT WITH A NUMBER AS KEY");

const object = {};

object[10] = "First value";
console.log(object[10]); // First value
object["10"] = "Second value";
console.log(object[10]); // Second value
console.log(Object.keys(object)); // [ '10' ]


console.log("\n3. OBJECT WITH ANOTHER OBJECT AS KEY");

const key1 = {};
const key2 = {};
const data = {};

data[key1] = "First";
data[key2] = "Second";
console.log(data[key1]); // Second
console.log(data[key2]); // Second
console.log(Object.keys(data)); // [ '[object Object]' ]

const customKey = {
    toString() {
        return "special";
    }
};

data[customKey] = "Third";
console.log(data["special"]);
console.log(Object.keys(data)); // ['[object Object]', 'special']


console.log("\n4. ARRAY WITH A STRING AS KEY");

const array = ["A", "B", "E"];
console.log(array[0]); // A
console.log(array["1"]); // B
array["name"] = "Jan";
console.log(array["name"]); // Jan
console.log(array); // [ 'A', 'B', 'E', name: 'Jan' ]
console.log(array.length); // 3
console.log(Object.keys(array)); // [ '0', '1', '2', 'name' ]


console.log("\n5. ARRAY WITH AN OBJECT AS KEY");

const index = {};
array[index] = "New value";
console.log(array[index]); // New value
console.log(array["[object Object]"]); // New value
console.log(array.length); // 3


console.log("\n6. DECREASING ARRAY LENGTH");

const numbers = [10, 20, 30, 40, 50];
console.log(numbers); // [ 10, 20, 30, 40, 50 ]
console.log(numbers.length); // 5
numbers.length = 2;
console.log(numbers); // [ 10, 20 ]
console.log(numbers.length); // 2


console.log("\n7. INCREASING ARRAY LENGTH");

numbers.length = 5;
console.log(numbers); // [ 10, 20, <3 empty items> ]
console.log(numbers.length); // 5
console.log(numbers[0]); // 10
console.log(numbers[2]); // undefined
console.log(2 in numbers); // false