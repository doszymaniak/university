function divisors_iter(n) {
    var result = [];
    for (var i = 2; i <= n; i++) {
        while (n % i == 0) {
            result.push(i);
            n /= i;
        }
    }
    return result;
}

function divisors_func(n) {
    function aux(n, d) {
        if (n == 1)
            return [];
        if (n % d === 0)
            return [d].concat(aux(n / d, d));
        return aux(n, d + 1);
    }
    return aux(n, 2);
}

console.log(divisors_iter(10))
console.log(divisors_iter(20))
console.log(divisors_func(10));
console.log(divisors_func(20));