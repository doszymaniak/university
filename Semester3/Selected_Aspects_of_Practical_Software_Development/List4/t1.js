function getLastProto(o) {
  let proto = Object.getPrototypeOf(o);
  while (Object.getPrototypeOf(proto) != null) {
    proto = Object.getPrototypeOf(proto);
  }
  return proto;
}

let object1 = {};
let object2 = { name: "Jan" };
let object3 = [1, 2, 3];
let object4 = new Date();
let object5 = function () {
  return 0;
};

let p1 = getLastProto(object1);
let p2 = getLastProto(object2);
let p3 = getLastProto(object3);
let p4 = getLastProto(object4);
let p5 = getLastProto(object5);

console.log(p1 === p2);
console.log(p1 === p3);
console.log(p1 === p4);
console.log(p1 === p5);
console.log(p1 === Object.prototype);
