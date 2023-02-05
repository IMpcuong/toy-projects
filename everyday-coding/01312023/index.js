//#region

const AdvancedHuman = class extends Object {
  static defaultName = "IMpcuong";
  static defaultAge = "23";

  // NOTE: A class may only have one constructor.
  /**
   *
   * @param {String} _name
   * @param {Number} _age
   */
  constructor(_name, _age) {
    super(_name, _age);
    if (!_name instanceof String || !_age instanceof Number) {
      this.name = this.defaultName;
      this.age = this.defaultName;
    }
    this.name = _name;
    this.age = _age;
  }

  // Getters:
  /**
   * @returns {String} A concatenation from each field's value.
   */
  get values() {
    return this.concatPropsVal();
  }

  // Setters:
  /**
   * @param {String} _name
   */
  set descName(_name) {
    this.name = `My name is ${_name}`;
  }

  /**
   * @param {Number} _age
   */
  set descAge(_age) {
    this.age = `Current age: ${_age}`;
  }

  // Methods:
  concatPropsVal() {
    return [...this.getFields()].join(", ");
  }

  // Generator method:
  *getFields() {
    yield this.name;
    yield this.age;
  }
}

// Type: `Map<Number, AdvancedHuman>`.
/**
 * @type {Map<Number, AdvancedHuman>}
 */
let grownMap = new Map();

// NOTE: Define custom properties for the built-in `Map` type.
// NOTE: Deprecated in some browsers.
grownMap.__defineGetter__("getKeys", function() {
  return [...grownMap.keys()];
});
// NOTE: Deprecated in some browsers.
grownMap.__defineGetter__("getValues", function() {
  let ret = [];
  grownMap.getKeys.forEach((k) => {
    ret.push(grownMap.get(k).values);
  });
  return ret;
});

Object.defineProperty(grownMap, "firstElement", {
  get() {
    return grownMap.size > 0 && grownMap.has(0)
      ? grownMap.get(0).values
      : Object.create(null);
  },
  configurable: true,
  enumerable: true,
});

const values = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
let indices = new Uint8Array(values);

// NOTE: Function-star or generator function:
let iterable = (function* (array) {
  yield* array;
})(values); // NOTE: Analogy/equivalent with the closure/lambda/anonymous function syntax in Golang.

// Another implementation method:
// let iterable = (function* () {
//   yield* values;
// })()

if (indices.length <= 10) {
  indices = new Uint8Array(iterable);
  console.log("Index array: ", indices);
}

// NOTE: `null` objects declaration methods:
const obj1 = Object.create(null);
const obj2 = { __proto__: null };
const obj3 = new Object();
console.info("Null object assignments:", obj1)
console.info("Null object assignments:", obj2);
console.info("Null object assignments:", obj3);

// NOTE: Reassure the object is an instance of array type.
// if (!Array.isArray(values)) return;

// Update data for our null map:
indices.forEach((i) => {
  const newAge = i !== 0 ? Math.pow(i, 2) : i;
  const impc = new AdvancedHuman(AdvancedHuman.defaultName, newAge.toFixed());
  grownMap.set(i, AdvancedHuman.create(impc));
});

const extraHuman = new AdvancedHuman();
extraHuman.descName = "NakedDragonJuly";
extraHuman.descAge = AdvancedHuman.defaultAge;
grownMap.set(indices.length, extraHuman);
console.log(grownMap);

for (const [key, human] of grownMap) {
  const fields = [...human.getFields()].join(", ");
  const stillFields = human instanceof AdvancedHuman ? human.values : undefined;
  console.log(`Key ${key} = Value {${fields}} || {${stillFields}}`);
}

grownMap.forEach((e) => console.log("Avant-gardist:", typeof e, e instanceof AdvancedHuman, e.values));
console.log("1. First element:", grownMap.firstElement);
console.log("2. List all keys:", grownMap.getKeys.map((k, i) => {
  return k*i % 2 === 0 ? parseInt([k-1, k].join(""), 10) : k
}));
console.log("3. List of values:", grownMap.getValues);

/**
 *
 * @param {Object} object
 * @returns {String} A new Object with its property satisfies `Object.__proto__ = true`.
 */
function singletonConversion(object) {
  let singleton = object.__proto__;
  if (!singleton.__singleton__) return null;

  singleton = new Object();
  Object.defineProperty(singleton, {
    __singleton__: { values: true },
  });
  singleton.__proto__ = object.__proto__;
  object.__proto__ = singleton;

  return object;
}

grownMap = singletonConversion(grownMap);
console.log(typeof grownMap, grownMap); // Out: `object null`.

// Output:
//
// ```
// Index array:  Uint8Array(10) [
//   0, 1, 2, 3, 4,
//   5, 6, 7, 8, 9
// ]
// Null object assignments: [Object: null prototype] {}
// Null object assignments: [Object: null prototype] {}
// Null object assignments: {}
// Map(11) {
//   0 => AdvancedHuman {},
//   1 => AdvancedHuman {},
//   2 => AdvancedHuman {},
//   3 => AdvancedHuman {},
//   4 => AdvancedHuman {},
//   5 => AdvancedHuman {},
//   6 => AdvancedHuman {},
//   7 => AdvancedHuman {},
//   8 => AdvancedHuman {},
//   9 => AdvancedHuman {},
//   10 => AdvancedHuman {
//     name: 'My name is NakedDragonJuly',
//     age: 'Current age: 23'
//   },
//   getKeys: [Getter],
//   getValues: [Getter],
//   firstElement: [Getter]
// }
// Key 0 = Value {IMpcuong, 0} || {IMpcuong, 0}
// Key 1 = Value {IMpcuong, 1} || {IMpcuong, 1}
// Key 2 = Value {IMpcuong, 4} || {IMpcuong, 4}
// Key 3 = Value {IMpcuong, 9} || {IMpcuong, 9}
// Key 4 = Value {IMpcuong, 16} || {IMpcuong, 16}
// Key 5 = Value {IMpcuong, 25} || {IMpcuong, 25}
// Key 6 = Value {IMpcuong, 36} || {IMpcuong, 36}
// Key 7 = Value {IMpcuong, 49} || {IMpcuong, 49}
// Key 8 = Value {IMpcuong, 64} || {IMpcuong, 64}
// Key 9 = Value {IMpcuong, 81} || {IMpcuong, 81}
// Key 10 = Value {My name is NakedDragonJuly, Current age: 23} || {My name is NakedDragonJuly, Current age: 23}
// Avant-gardist: object true IMpcuong, 0
// Avant-gardist: object true IMpcuong, 1
// Avant-gardist: object true IMpcuong, 4
// Avant-gardist: object true IMpcuong, 9
// Avant-gardist: object true IMpcuong, 16
// Avant-gardist: object true IMpcuong, 25
// Avant-gardist: object true IMpcuong, 36
// Avant-gardist: object true IMpcuong, 49
// Avant-gardist: object true IMpcuong, 64
// Avant-gardist: object true IMpcuong, 81
// Avant-gardist: object true My name is NakedDragonJuly, Current age: 23
// 1. First element: IMpcuong, 0
// 2. List all keys: [
//   -10,  1, 12,  3, 34,
//     5, 56,  7, 78,  9,
//   910
// ]
// 3. List of values: [
//   'IMpcuong, 0',
//   'IMpcuong, 1',
//   'IMpcuong, 4',
//   'IMpcuong, 9',
//   'IMpcuong, 16',
//   'IMpcuong, 25',
//   'IMpcuong, 36',
//   'IMpcuong, 49',
//   'IMpcuong, 64',
//   'IMpcuong, 81',
//   'My name is NakedDragonJuly, Current age: 23'
// ]
// object null
// ```

//#endregion