function createGenerator(limit) {
    var _state = 0;
    return {
        next: function () {
            return {
                value: _state,
                done: _state++ >= limit
            }
        }
    }
}

var foo1 = {
    [Symbol.iterator]: function () { return createGenerator(10) }
};

for (var f of foo1)
    console.log(f);

var foo2 = {
    [Symbol.iterator]: function () { return createGenerator(5) }
};

for (var f of foo2)
    console.log(f);