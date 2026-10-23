function is_prime(num) {
    if (num < 2) return false;
    var sq = Math.sqrt(num);
    for (var i = 2; i <= sq; i++) {
        if (num % i === 0)
            return false;
    }
    return true;
}

var numbers = [];

for (var i = 2; i <= 100000; i++) {
    if (is_prime(i))
        numbers.push(i);
}

let text = JSON.stringify(numbers);
console.log(text);