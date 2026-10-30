var cnt = {
    _value: 0,

    increment: function () {
        this._value++;
    },

    get val() {
        return this._value;
    },

    set val(i) {
        this._value = i;
    }
};

console.log(cnt.val);

cnt.increment();
console.log(cnt.val);

cnt.val = 7;
console.log(cnt.val);

// Dodawanie nowego pola
cnt.step = 1;

// Dodawanie nowej metody
cnt.increment = function () {
    cnt._value += cnt.step;
};

// Dodawanie nowej wlasciwosci z get i set
Object.defineProperty(cnt, 'get_17', {
    get: function () {
        return 17;
    },
    set: function (i) {
        cnt._value = i;
    }
});

cnt.increment();
console.log(cnt.val);

console.log(cnt.get_17);

cnt.get_17 = 20;
console.log(cnt.val);

// Pola i metody mozna dodawac za pomoca zwyklego przypisania
// Wlasciwosci z get i set mozna dodawac do istniejacego obiektu 
// tylko za pomoca Object.defineProperty()