function should_be_added(num) {
    if (num === 0) {
        return false;
    }
    var sum = 0, original_num = num;
    while (num > 0) {
        var digit = num % 10;
        num = Math.floor(num / 10);
        if (digit === 0 || original_num % digit != 0) {
            return false;
        }
        sum += digit;
    }
    return original_num % sum === 0;
}

var numbers = [];

for (var i = 1; i <= 100000; i++) {
    if (should_be_added(i)) {
        numbers.push(i);
    }
}

let text = JSON.stringify(numbers);
console.log(text);