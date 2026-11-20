function Tree(val, left, right) {
    this.left = left;
    this.right = right;
    this.val = val;
}

Tree.prototype[Symbol.iterator] = function* () {
    yield this.val;
    if (this.left) yield* this.left;
    if (this.right) yield* this.right;
}

Tree.prototype[Symbol.iterator] = function* () {
    const queue = [];
    queue.push(this);
    while (queue.length > 0) {
        let current = queue[0];
        queue.splice(0, 1);
        if (current.right)
            queue.push(current.right);
        if (current.left)
            queue.push(current.left);
        yield current.val;
    }
}

var root = new Tree(1,
    new Tree(2, new Tree(3)), new Tree(4));

for (var e of root) {
    console.log(e);
}
// 1 2 3 4