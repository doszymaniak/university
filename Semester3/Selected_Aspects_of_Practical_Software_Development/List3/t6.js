function fib_next() {
    var _first = 0, _second = 1;
    return {
        next: function () {
            var _value = _first;
            _first = _second;
            _second = _value + _second;
            return {
                value: _value,
                done: false
            }
        }
    }
}

function* fib_gen() {
    let a = 0, b = 1;
    while (true) {
        yield a;
        [a, b] = [b, a + b];
    }
}

console.log("FIB_NEXT()")
const iterator1 = fib_next();
for (let i = 0; i < 10; i++) console.log(iterator1.next().value);

console.log("\nFIB_GEN()")
const iterator2 = fib_gen();
for (let i = 0; i < 10; i++) console.log(iterator2.next().value)

/*
for (var i of fib_gen()) {
    console.log(i);
}
*/