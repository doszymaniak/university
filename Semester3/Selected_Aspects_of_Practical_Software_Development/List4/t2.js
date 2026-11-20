var p = {
    name: 'jan'
}
var q = {
    surname: 'kowalski'
}

function isOwnProperty(obj, property) {
    return Object.prototype.hasOwnProperty.call(obj, property);
}

Object.setPrototypeOf(p, q);

console.log(isOwnProperty(p, "name")); // true
console.log(isOwnProperty(p, "surname")); // false

console.log();

for (let key of Object.keys(p))
    console.log(key, p[key])

console.log();

// Przechodzi rowniez po wlasciwosciach odziedziczonych
for (let key in p)
    console.log(key, p[key])