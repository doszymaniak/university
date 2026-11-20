function pipe(xs, ...[f, ...fs]) {
    return f ? pipe(f(xs), ...fs) : xs;
}

function map(f) {
    return function (xs) {
        return xs.map(f);
    }
}

function groupBy(keySelector) {
    return function (xs) {
        const object = Object.groupBy(xs, keySelector);
        const keys = Object.keys(object);
        return map(function (key) {
            const group = object[key];
            group.key = key;
            return group;
        })(keys);
    }
}

function sort(keySelector) {
    return function (xs) {
        return xs.sort(function (a, b) {
            const a_val = keySelector(a)
            const b_val = keySelector(b)
            if (a_val < b_val) return -1;
            if (a_val > b_val) return 1;
            return 0;
        })
    }
}

function take(n) {
    return function (xs) {
        return xs.slice(0, n);
    }
}


const people = [
    { name: 'jan', surname: 'kowalski' },
    { name: 'jan', surname: 'malinowski' },
    { name: 'tomasz', surname: 'baranowski' },
    { name: 'jan', surname: 'nowak' },
    { name: 'tomasz', surname: 'kochanowski' }
];

const ip = [
    { ip: '192.168.0.1' },
    { ip: '192.168.0.1' },
    { ip: '192.168.0.2' },
    { ip: '192.168.0.2' },
    { ip: '192.168.0.3' },
    { ip: '192.168.0.17' },
    { ip: '192.168.0.1' }
]

const object = Object.groupBy(people, e => e.name)

console.log(pipe(people, groupBy(e => e.name)))

console.log(pipe(
    ip,
    groupBy(e => e.ip),
    sort(g => -g.length),
    take(3),
    map(a => ({ ip: a.key, count: a.length }))
))