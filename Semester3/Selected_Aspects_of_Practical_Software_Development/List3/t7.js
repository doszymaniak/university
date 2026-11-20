function* fib() {
    let a = 0, b = 1;
    while (true) {
        yield a;
        [a, b] = [b, a + b];
    }
}

function* take(it, top) {
    let i = 0;
    while (i <= top) {
        yield it.next().value;
        i++;
    }
}

for (let num of take(fib(), 10)) {
    console.log(num);
}