function fib_rec(n) {
    if (n == 1 || n == 2) return 1;
    return fib_rec(n - 1) + fib_rec(n - 2);
}

function fib_iter(n) {
    if (n == 1 || n == 2) return 1;
    var a = 1, b = 1;
    for (var i = 2; i < n; i++) {
        var temp = b;
        b += a;
        a = temp;
    }
    return b;
}

function fib_cache(n) {
    if (n in cache)
        return cache[n];
    var result;
    if (n == 1 || n == 2) result = 1;
    else result = fib_cache(n - 1) + fib_cache(n - 2);
    cache[n] = result;
    return result;
}

/*
function memoize(fn) {
    var cache = {};
    return function (n) {
        if (n in cache)
            return cache[n];
        var result = fn(n);
        cache[n] = result;
        return result;
    }
}

var fib_cache = memoize(fib_rec);
*/

var results = [];
var cache = {};


for (var n = 10; n <= 40; n += 5) {
    var start_rec = performance.now();
    var res_rec = fib_rec(n);
    var time_rec = performance.now() - start_rec;

    var start_iter = performance.now();
    var res_iter = fib_iter(n);
    var time_iter = performance.now() - start_iter;

    cache = {};
    var start_cache = performance.now();
    var res_cache = fib_cache(n);
    var time_cache = performance.now() - start_cache;

    results.push({
        n: n,
        "result (rec)": res_rec,
        "time (rec) (ms)": time_rec.toFixed(4),
        "result (iter)": res_iter,
        "time (iter) (ms)": time_iter.toFixed(4),
        "time (cache) (ms)": time_cache.toFixed(4)
    });
}

console.table(results);